/*
 * Copyright (c) 2004  Morettoni Luca <luca@morettoni.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#include "zonenotify.h"

int main(int argc, char *argv[])
{
	int i = 2;
	int ret = 0;

	if (argc < 3) usage ();

	while (i < argc) {
		if (init_connection (argv[i]) != -1) {
			if (slave_notify (argv[1], argv[i]) == -1) ret = 1;
			stop_connection ();
		} else
			fprintf (stderr, "Can't connect to %s\n", argv[i]);
		i++;
	}

	exit (ret);
}

void usage ()
{
	printf ("%s, %s\n\nusage: zonenotify zone slave [slave 2 ... [slave n]] \n", VERSION, AUTHOR);
	printf ("where zone is the domain name to update on slave server ``slave''\n");
	exit (1);
}

/* connect to the nameserver */
int init_connection (const char *server)
{
	struct	sockaddr_in sa, sl;
	struct	hostent *he;
	int	isbind = 0;
	int	i;
	long	rand;
	time_t	now;

	time (&now);
	srandom ((long) now);

	s = socket (AF_INET, SOCK_DGRAM, 0);
	if (s < 0) return -1;

	/* local port: random */
	memset (&sl, 0, sizeof (sl));
	sl.sin_family = AF_INET;
	sl.sin_addr.s_addr = htonl (INADDR_ANY);

	for (i = 0; i < 12 && !isbind; i++) {
		rand = 1025+(random () % 15000);
		sl.sin_port = htons (rand);
		isbind = (bind (s, (struct sockaddr *) &sl, sizeof (sl)) == 0);
	}

	if (!isbind) return -1;

	/* destination port: nameserver (53) */
	memset (&sa, 0, sizeof (sa));
	if (inet_aton (server, &sa.sin_addr) == 0) {
		he = gethostbyname (server);

		if (he)
			memcpy (&sa.sin_addr, he->h_addr_list[0], sizeof (sa.sin_addr));
		else
			return -1;
	}

	sa.sin_family = AF_INET;
	sa.sin_port = htons (NAMESERVER_PORT);
	if (connect (s, (struct sockaddr *) &sa, sizeof (sa)) != 0)
		return -1;

	return 0;
}

/* close local socket */
void stop_connection (void)
{
	shutdown (s, SHUT_RDWR);
}

/* encode name string in ns query format */
int ns_encode (char *str, char *buff)
{
	char *pos;
	int size;
	int len = 0;

	while (1) {
		pos = (char *) strchr (str, '.');

		if (!pos) break;

		size = pos-str;
		*buff++ = size;

		strncpy (buff, str, size);
		buff += size;

		len += size+1;
		str = pos+1;
	}

	size = strlen (str);
	if (size) {
		*buff++ = size;
		strncpy (buff, str, size);
		buff += size;
		len += size+1;
	}

	*buff = 0;

	return len;
}

/* send sequest to our DNS-cache server */
int slave_notify (char *domain, const char *server)
{
	static int	unique = 0;
	char		buffer[PACKETSZ];
	char		name[MAXDNAME];
	HEADER		*hdr;
	int		len, reqlen;
	u_int16_t	val;
	fd_set		active_fd_set;
	struct timeval	tv_timeout;

	hdr = (HEADER*) buffer;
        hdr->qr = 0;
        hdr->opcode = NS_NOTIFY_OP;
        hdr->aa = 1;
        hdr->tc = 0;
        hdr->rd = 0;
        hdr->ra = 0;
        hdr->unused = 0;
        hdr->rcode = 0;
        hdr->qdcount = htons (1);
        hdr->ancount = 0;
        hdr->nscount = 0;
        hdr->arcount = 0;
        hdr->id = htons (unique++);

	/* the 0x00 at the end must be copied! */
	reqlen = ns_encode (domain, name)+1;
	memcpy (buffer+sizeof (HEADER), name, reqlen);

	/* query type */
	val = htons (T_SOA);
	memcpy (buffer+sizeof (HEADER)+reqlen, &val, 2);
	reqlen += 2;

	/* query class */
	val = htons(C_IN);
	memcpy (buffer+sizeof (HEADER)+reqlen, &val, 2);
	reqlen += 2;

	/* we wait max TIMEOUT seconds */
	tv_timeout.tv_sec = TIMEOUT;
	tv_timeout.tv_usec = 0;

	FD_ZERO (&active_fd_set);
	FD_SET (s, &active_fd_set);
	
	/* send the request to the nameserver */
	if (send (s, buffer, sizeof (HEADER)+reqlen, 0) == -1)
		return -1;

	/* we wait the answere */
	if (select (FD_SETSIZE, &active_fd_set, NULL, NULL, &tv_timeout) < 1)
	{
		fprintf (stderr, "%s: timeout\n", server);
		return -1;
	}

	/* and get back the answere */
	len = recv (s, buffer, PACKETSZ, 0);
	if (len != -1) {
		hdr = (HEADER*) buffer;

		if (hdr->qr && hdr->rcode) {
			fprintf (stderr, "%s: %s\n", 
					server, 
					hdr->rcode < 23 ? dns_errors[hdr->rcode] : "unknow error");
			return -1;
		}
	}

	return 0;
}
