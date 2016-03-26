/*
 * Copyright (c) 2006  mirabilos <m@mirbsd.org>
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
 * $MirOS: ports/net/djbdns/files/build/zonenotify/zonenotify.c,v 1.5 2006/08/10 15:31:57 tg Exp $
 * $Id$
 */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#ifdef _BSD
#include <arpa/nameser_compat.h>
#endif
#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "zonenotify.h"

__RCSID("$MirOS: ports/net/djbdns/files/build/zonenotify/zonenotify.c,v 1.5 2006/08/10 15:31:57 tg Exp $");

int
main(int argc, char *argv[])
{
	int i = 2;
	int ret = 0;

	if (argc < 3)
		usage ();

	while (i < argc) {
		if (init_connection (argv[i], argv[1]) == -1)
			ret = 1;
		i++;
	}

	return (ret);
}

__dead void
usage(void)
{
	printf ("%s, %s\n\nusage: zonenotify zone slave [slave 2 ... [slave n]] \n", VERSION, AUTHOR);
	printf ("where zone is the domain name to update on slave server ``slave''\n");
	printf ("this send a \"NOTIFY\" packet to slave1 (slave2...slaveN) about zone\n"
	    "\"zone\", if there are some problem zonenofity display the error message\n"
	    "and exit 1, otherwise exit 0.\n");
	exit (1);
}

/* connect to the nameserver */
int
init_connection(const char *server, const char *domain)
{
	struct addrinfo hints, *res, *res0;
	struct sockaddr_storage ss;
	struct sockaddr *ssp = (struct sockaddr *)&ss;
	socklen_t sssz;
	const char *cause = NULL;
	int i;
	int rv = 0;

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	if ((i = getaddrinfo(server, "domain", &hints, &res0))) {
		warnx("%s", gai_strerror(i));
		goto cant_connect;
	}
	s = -1;
	for (res = res0; res; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype,
		    res->ai_protocol);
		if (s < 0) {
			cause = "socket";
			continue;
		}
		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			cause = "connect";
			continue;
		}
		sssz = sizeof (ss);
		if (getpeername(s, ssp, &sssz) == 0) {
			char n[256];
			if (!getnameinfo(ssp, SA_LEN(ssp), n, 256, NULL,
			    0, NI_NUMERICHOST))
				printf("connecting to %s\n", n);
			else
				printf("getnameinfo failed\n");
		} else
			printf("getpeername failed\n");
		if (slave_notify(domain, server) == -1)
			rv = 1;
		else
			cause = NULL;
		close(s);
	}
	if (cause) {
		warn("couldn't %s", cause);
 cant_connect:
		fprintf(stderr, "%s: couldn't connect\n", server);
	}
	freeaddrinfo(res0);

	return (rv);
}

/* encode name string in ns query format */
int
ns_encode(const char *str, char *buff)
{
	const char *pos;
	int size;
	int len = 0;

	while (1) {
		pos = (const char *) strchr (str, '.');

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
int
slave_notify(const char *domain, const char *server)
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
					hdr->rcode < 23 ? dns_errors[hdr->rcode] : "unknown error");
			return -1;
		}
	}

	return 0;
}
