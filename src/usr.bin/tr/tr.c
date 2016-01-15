/*	$OpenBSD: tr.c,v 1.13 2004/09/15 22:12:19 deraadt Exp $	*/
/*	$NetBSD: tr.c,v 1.5 1995/08/31 22:13:48 jtc Exp $	*/

/*
 * Copyright (c) 2007, 2008, 2009, 2014, 2016
 *	mirabilos <m@mirbsd.org>
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

#include <sys/types.h>

#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <locale.h>
#include <stdbool.h>
#include <mbfun.h>
#include <wctype.h>

#include "extern.h"

__COPYRIGHT("@(#) Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
__SCCSID("@(#)tr.c	8.2 (Berkeley) 5/4/95");
__RCSID("$MirOS: src/usr.bin/tr/tr.c,v 1.8 2016/01/02 21:33:19 tg Exp $");

static wchar_t string1[NCHARS], string2[NCHARS];

STR s1 = {
	.which = STRING1,
	.state = NORMAL,
	.cnt = 0,
	.lastch = OOBCH,
	.equiv = { 0, OOBCH },
	.set = NULL,
	.use_wctrans = false,
	.str = NULL
};
STR s2 = {
	.which = STRING2,
	.state = NORMAL,
	.cnt = 0,
	.lastch = OOBCH,
	.equiv = { 0, OOBCH },
	.set = NULL,
	.use_wctrans = false,
	.str = NULL
};

static void setup(wchar_t *, char *, STR *, bool);
static void usage(void) __dead;

#define getwcf() __extension__({				\
	wint_t getwcf_c;					\
								\
	if ((getwcf_c = getwchar()) == WEOF && ferror(stdin) &&	\
	    errno == EILSEQ) {					\
		clearerr(stdin);				\
		getwcf_c = 0xFFFD;				\
	}							\
	(getwcf_c);						\
})

int
main(int argc, char *argv[])
{
	wint_t ch;
	wchar_t cnt, lastch, *p;
	int ich;
	bool cflag, dflag, sflag, isstring2;

	setlocale(LC_ALL, "");

	for (lastch = 0; lastch < NCHARS; ++lastch)
		string1[lastch] = lastch;

	cflag = dflag = sflag = false;
	while ((ich = getopt(argc, argv, "cds")) != -1)
		switch (ich) {
		case 'c':
			cflag = true;
			break;
		case 'd':
			dflag = true;
			break;
		case 's':
			sflag = true;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	switch(argc) {
	case 0:
	default:
		usage();
		/* NOTREACHED */
	case 1:
		isstring2 = false;
		break;
	case 2:
		isstring2 = true;
		break;
	}

	/*
	 * tr -ds [-c] string1 string2
	 * Delete all characters (or complemented characters) in string1.
	 * Squeeze all characters in string2.
	 */
	if (dflag && sflag) {
		if (!isstring2)
			usage();

		setup(string1, argv[0], &s1, cflag);
		setup(string2, argv[1], &s2, false);

		for (lastch = OOBCH; (ch = getwcf()) != WEOF; )
			if (!string1[ch] && (!string2[ch] || lastch != ch)) {
				lastch = ch;
				putwchar(ch);
			}
		exit(0);
	}

	/*
	 * tr -d [-c] string1
	 * Delete all characters (or complemented characters) in string1.
	 */
	if (dflag) {
		if (isstring2)
			usage();

		setup(string1, argv[0], &s1, cflag);

		while ((ch = getwcf()) != WEOF)
			if (!string1[ch])
				putwchar(ch);
		exit(0);
	}

	/*
	 * tr -s [-c] string1
	 * Squeeze all characters (or complemented characters) in string1.
	 */
	if (sflag && !isstring2) {
		setup(string1, argv[0], &s1, cflag);

		for (lastch = OOBCH; (ch = getwcf()) != WEOF; )
			if (!string1[ch] || lastch != ch) {
				lastch = ch;
				putwchar(ch);
			}
		exit(0);
	}

	/*
	 * tr [-cs] string1 string2
	 * Replace all characters (or complemented characters) in string1 with
	 * the character in the same position in string2.  If the -s option is
	 * specified, squeeze all the characters in string2.
	 */
	if (!isstring2)
		usage();

	s1.str = ambstowcs(argv[0]);
	s2.str = ambstowcs(argv[1]);
	if ((strstr(argv[0], "[:lower:]") && strstr(argv[1], "[:upper:]")) ||
	    (strstr(argv[1], "[:lower:]") && strstr(argv[0], "[:upper:]"))) {
		s1.use_wctrans = true;
		s2.use_wctrans = true;
	}

	if (cflag)
		for (cnt = NCHARS, p = string1; cnt--;)
			*p++ = OOBCH;

	if (!next(&s2))
		errx(1, "empty string2");

	/* If string2 runs out of characters, use the last one specified. */
	ch = s2.lastch;
	if (sflag)
		while (next(&s1)) {
			string1[s1.lastch] = ch = s2.lastch;
			string2[ch] = 1;
			(void)next(&s2);
		}
	else
		while (next(&s1)) {
			string1[s1.lastch] = ch = s2.lastch;
			(void)next(&s2);
		}

	if (cflag)
		for (cnt = 0, p = string1; cnt < NCHARS; ++p, ++cnt)
			*p = *p == OOBCH ? ch : cnt;

	if (sflag)
		for (lastch = OOBCH; (ch = getwcf()) != WEOF;) {
			ch = string1[ch];
			if (!string2[ch] || lastch != ch) {
				lastch = ch;
				putwchar(ch);
			}
		}
	else
		while ((ch = getwcf()) != WEOF)
			putwchar(string1[ch]);
	exit(0);
}

static void
setup(wchar_t *string, char *arg, STR *str, bool cflag)
{
	wchar_t cnt, *p;

	str->str = ambstowcs(arg);
	bzero(string, NCHARS * sizeof (wchar_t));
	while (next(str))
		string[str->lastch] = 1;
	if (cflag)
		for (p = string, cnt = NCHARS; cnt--; ++p)
			*p = !*p;
}

static void
usage(void)
{
	fprintf(stderr, "usage:\ttr [-cs] string1 string2\n"
	    "\ttr [-c] -d string1\n"
	    "\ttr [-c] -s string1\n"
	    "\ttr [-c] -ds string1 string2\n");
	exit(1);
}
