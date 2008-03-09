/**	$MirOS$ */
/*	$OpenBSD: what.c,v 1.11 2003/07/10 00:06:52 david Exp $	*/
/*	$NetBSD: what.c,v 1.4 1994/12/20 16:01:03 jtc Exp $	*/

/*
 * Copyright (c) 1980, 1988, 1993
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

#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__COPYRIGHT("Copyright (c) 1980, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
__SCCSID("@(#)what.c	8.1 (Berkeley) 6/6/93");
__RCSID("$MirOS$");

static void search(void);
static __dead void usage(void);

static int matches;
static int sflag;

extern const char *__progname;

/*
 * what
 */
/* ARGSUSED */
int
main(int argc, char *argv[])
{
	int c;

	matches = sflag = 0;
	while ((c = getopt(argc, argv, "s")) != -1) {
		switch (c) {
		case 's':
			sflag = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		printf("/dev/stdin\n");
		search();
	} else do {
		if (!freopen(*argv, "r", stdin)) {
			perror(*argv);
			exit(matches ? 0 : 1);
		}
		printf("%s\n", *argv);
		search();
	} while(*++argv);
	exit(matches ? 0 : 1);
}

static void
search(void)
{
	int c;

	while ((c = getchar()) != EOF) {
 loop:
		if (c != '@')
			continue;
		if ((c = getchar()) != '(')
			goto loop;
		if ((c = getchar()) != '#')
			goto loop;
		if ((c = getchar()) != ')')
			goto loop;
		putchar('\t');
		while ((c = getchar()) != EOF && c && c != '"' &&
		    c != '>' && c != '\n' && c != '\\')
			putchar(c);
		putchar('\n');
		matches++;
		if (sflag)
			break;
	}
}

static void
usage(void)
{
	fprintf(stderr, "usage: %s [-s] [file [...]]\n", __progname);
	exit(1);
}
