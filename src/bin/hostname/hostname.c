/*	$OpenBSD: hostname.c,v 1.7 2003/06/02 23:32:08 millert Exp $	*/
/*	$NetBSD: hostname.c,v 1.10 1995/09/07 06:28:40 jtc Exp $	*/

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
__COPYRIGHT("@(#) Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
__SCCSID("@(#)hostname.c	8.2 (Berkeley) 4/28/95");
__RCSID("$MirOS$");

#include <sys/socket.h>
#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern	char *__progname;

__dead void usage(void);

int
main(int argc, char *argv[])
{
	int ch;
	int type = 0;
	char *p, hostname[MAXHOSTNAMELEN];

	while ((ch = getopt(argc, argv, "fs")) != -1)
		switch (ch) {
		case 'f':
			type = 2;
			break;
		case 's':
			type = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 1)
		usage();

	if (*argv) {
		if (type)
			usage();
		if (sethostname(*argv, strlen(*argv)))
			err(1, "sethostname");
	} else {
		if (gethostname(hostname, sizeof(hostname)))
			err(1, "gethostname");
		if (type == 2) {
			struct addrinfo *res, hints;

			memset(&hints, 0, sizeof(struct addrinfo));
			hints.ai_socktype = SOCK_DGRAM;
			hints.ai_flags = AI_CANONNAME;
			if ((type = getaddrinfo(hostname, NULL, &hints, &res)))
				errx(1, "%s", gai_strerror(type));
			strlcpy(hostname, res->ai_canonname, sizeof(hostname));
		} else if ((type == 1) && (p = strchr(hostname, '.')))
			*p = '\0';
		(void)printf("%s\n", hostname);
	}
	exit(0);
}

void
usage(void)
{
	fprintf(stderr, "usage: %s [-fs | <name-of-host>]\n", __progname);
	exit(1);
}
