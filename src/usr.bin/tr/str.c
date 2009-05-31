/*	$OpenBSD: str.c,v 1.9 2004/09/15 22:12:19 deraadt Exp $	*/
/*	$NetBSD: str.c,v 1.7 1995/08/31 22:13:47 jtc Exp $	*/

/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 1991, 1993
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

#include <errno.h>
#include <err.h>
#include <stdbool.h>
#include <wctype.h>

#include "extern.h"

__SCCSID("@(#)str.c	8.2 (Berkeley) 4/28/95");
__RCSID("$MirOS: src/usr.bin/tr/str.c,v 1.3 2007/07/15 19:28:39 tg Exp $");

static wchar_t	backslash(STR *);
static bool	bracket(STR *);
static void	genclass(STR *);
static void	genequiv(STR *);
static bool	genrange(STR *);
static void	genseq(STR *);

bool
next(STR *s)
{
	wchar_t ch;

	switch (s->state) {
	case EOS:
		return (false);
	case INFINITE:
		return (true);
	case NORMAL:
		switch (ch = *s->str) {
		case '\0':
			s->state = EOS;
			return (false);
		case '\\':
			s->lastch = backslash(s);
			break;
		case '[':
			if (bracket(s))
				return (next(s));
			/* FALLTHROUGH */
		default:
			++s->str;
			s->lastch = ch;
			break;
		}

		/* We can start a range at any time. */
		if (s->str[0] == L'-' && genrange(s))
			return (next(s));
		return (true);
	case RANGE:
		if (s->cnt-- == 0) {
			s->state = NORMAL;
			return (next(s));
		}
		++s->lastch;
		return (true);
	case SEQUENCE:
		if (s->cnt-- == 0) {
			s->state = NORMAL;
			return (next(s));
		}
		return (true);
	case SET:
		if ((s->lastch = s->set[s->cnt++]) == OOBCH) {
			s->state = NORMAL;
			return (next(s));
		}
		return (true);
	case WCLASS:
		while (s->cnext != OOBCH) {
			if (iswctype(s->cnext, s->wclass))
				break;
			s->cnext++;
		}
		if (s->cnext == OOBCH) {
			s->state = NORMAL;
			return (next(s));
		}
		s->lastch = s->cnext++;
		return (true);
	case WTRANS:
		while (s->cnext != OOBCH) {
			if (iswctype(s->cnext, s->wclass) &&
			    (ch = towctrans(s->cnext, s->wtrans)) != s->cnext) {
				s->lastch = s->which == STRING1 ? s->cnext : ch;
				s->cnext++;
				return (true);
			}
			s->cnext++;
		}
		s->state = NORMAL;
		return (next(s));
	default:
		return (false);
	}
	/* NOTREACHED */
}

static bool
bracket(STR *s)
{
	wchar_t *p;

	switch (s->str[1]) {
	case L':':				/* "[:class:]" */
		if ((p = wcsstr(s->str + 2, L":]")) == NULL)
			return (false);
		*p = L'\0';
		s->str += 2;
		genclass(s);
		s->str = p + 2;
		return (true);
	case L'=':				/* "[=equiv=]" */
		if ((p = wcsstr(s->str + 2, L"=]")) == NULL)
			return (false);
		s->str += 2;
		genequiv(s);
		return (true);
	default:				/* "[\###*n]" or "[#*n]" */
		if ((p = wcspbrk(s->str + 2, L"*]")) == NULL)
			return (false);
		if (p[0] != L'*' || wcschr(p, L']') == NULL)
			return (false);
		s->str += 1;
		genseq(s);
		return (true);
	}
	/* NOTREACHED */
}

static void
genclass(STR *s)
{
	wctype_t tmp;
	size_t len;
	char *cp;
	bool alower;

	if (s->use_wctrans && ((alower = !wcscmp(s->str, L"lower")) ||
	    !wcscmp(s->str, L"upper"))) {
		alower = (alower && s->which == STRING1) ||
		    (!alower && s->which == STRING2);
		s->wclass = alower ? wctype("lower") : wctype("upper");
		s->wtrans = alower ? wctrans("toupper") : wctrans("tolower");
		s->state = WTRANS;
		s->cnext = 0;
		return;
	}

	len = wcstombs(NULL, s->str, 0);
	if ((cp = malloc(len + 1)) == NULL)
		err(1, "out of memory allocating %zu bytes", len);
	wcstombs(cp, s->str, len + 1);

	if ((tmp = wctype(cp)) == 0)
		errx(1, "unknown class %s", cp);

	free(cp);
	s->state = WCLASS;
	s->wclass = tmp;
	s->cnext = 0;
}

/*
 * English doesn't have any equivalence classes, so for now
 * we just syntax check and grab the character.
 */
static void
genequiv(STR *s)
{
	if (*s->str == L'\\') {
		s->equiv[0] = backslash(s);
		if (*s->str != L'=')
			errx(1, "misplaced equivalence equals sign");
	} else {
		s->equiv[0] = s->str[0];
		if (s->str[1] != L'=')
			errx(1, "misplaced equivalence equals sign");
	}
	s->str += 2;
	s->cnt = 0;
	s->state = SET;
	s->set = s->equiv;
}

static bool
genrange(STR *s)
{
	wchar_t stopval, *savestart;

	savestart = s->str;
	stopval = *++s->str == L'\\' ? backslash(s) : *s->str++;
	if (stopval < s->lastch) {
		s->str = savestart;
		return (false);
	}
	s->cnt = stopval - s->lastch + 1;
	s->state = RANGE;
	--s->lastch;
	return (true);
}

static void
genseq(STR *s)
{
	wchar_t *ep;

	if (s->which == STRING1)
		errx(1, "sequences only valid in string2");

	if (*s->str == L'\\')
		s->lastch = backslash(s);
	else
		s->lastch = *s->str++;
	if (*s->str != L'*')
		errx(1, "misplaced sequence asterisk");

	switch (*++s->str) {
	case L'\\':
		s->cnt = backslash(s);
		break;
	case L']':
		s->cnt = 0;
		++s->str;
		break;
	default:
		if (iswdigit(*s->str)) {
			s->cnt = wcstol(s->str, &ep, 0);
			if (*ep == L']') {
				s->str = ep + 1;
				break;
			}
		}
		errx(1, "illegal sequence count");
		/* NOTREACHED */
	}

	s->state = s->cnt ? SEQUENCE : INFINITE;
}

/*
 * Translate \??? into a character.  Up to 3 octal digits, if no digits either
 * an escape code or a literal character.  Spew out a MirOS OPTU-16 raw octet.
 */
static wchar_t
backslash(STR *s)
{
	wchar_t ch, cnt, val;

	for (cnt = val = 0;;) {
		ch = *++s->str;
		if (ch < L'0' || ch > L'7')
			break;
		val = val * 8 + ch - L'0';
		if (++cnt == 3) {
			++s->str;
			break;
		}
	}
	if (cnt)
		return ((val &= 0xFF) < 0x80 ? val : 0xEF00 | val);
	if (ch != L'\0')
		++s->str;
	switch (ch) {
		case L'a':			/* escape characters */
			return (L'\7');
		case L'b':
			return (L'\b');
		case L'f':
			return (L'\f');
		case L'n':
			return (L'\n');
		case L'r':
			return (L'\r');
		case L't':
			return (L'\t');
		case L'v':
			return (L'\13');
		case L'\0':			/*  \" -> \ */
			s->state = EOS;
			return (L'\\');
		default:			/* \x" -> x */
			return (ch);
	}
}
