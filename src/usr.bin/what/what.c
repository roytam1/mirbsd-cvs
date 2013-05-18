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

#ifndef lint
static char copyright[] =
"@(#) Copyright (c) 1980, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)what.c	8.1 (Berkeley) 6/6/93";
#endif
static char rcsid[] = "$MirOS$";
#endif /* not lint */

#include <sys/types.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

void search(char *);

static const char match2[] = "MirBSD: ";

/*
 * what
 */
/* ARGSUSED */
int
main(int argc, char *argv[])
{
	struct utsname utsn;
	char match[256];

	if (uname(&utsn) == -1)
		err(1, "uname");
	strlcpy(match, utsn.sysname, sizeof match);

	if (!*++argv) 
		search(match);
	else do {
		if (!freopen(*argv, "r", stdin)) {
			perror(*argv);
			exit(1);
		}
		printf("%s\n", *argv);
		search(match);
	} while(*++argv);
	exit(0);
}

void
search(char *match)
{
	int c;
	int i;
	int j0, j1, j2, jl;

	while ((c = getchar()) != EOF) {
loop:		if (c == '$') {
			j1 = strlen(match);
			j2 = strlen(match2);
			j0 = (j1>j2) ? j1 : j2;
			for (i = 0; i < j0; ++i) {
				if ((i == j1) && (jl == 1))
					break;
				if ((i == j2) && (jl == 2))
					break;
				c = getchar();
				if (i < j1)
					if (c == match[i]) {
						jl = 1;
						continue;
					}
				if (i < j2)
					if (c == match2[i]) {
						jl = 2;
						continue;
					}
				goto loop;
			}
			printf("\t$%s", ((jl==1) ? match : match2));
			while (isprint(c = getchar()))
				putchar(c);
			putchar('\n');
			goto loop;
		}
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
	}
}
