/* $MirOS: src/lib/libc/gen/isctype.c,v 1.7 2007/02/02 21:06:19 tg Exp $ */

/*-
 * Copyright (c) 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#define _ANSI_LIBRARY
#include <ctype.h>
#include <stdio.h>

__RCSID("$MirOS: src/lib/libc/gen/isctype.c,v 1.7 2007/02/02 21:06:19 tg Exp $");

#undef isalnum
#undef isalpha
#undef isascii
#undef isbinry
#undef isblank
#undef iscntrl
#undef isdigit
#undef isgraph
#undef islower
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit
#undef toascii
#undef tolower
#undef toupper

#define __CTYPE_IMPL2(t)			\
	int is ## t (int c)			\
	{					\
		return __CTYPE_IMPL(c,t);	\
	}

__CTYPE_IMPL2(alnum)
__CTYPE_IMPL2(alpha)
__CTYPE_IMPL2(blank)
__CTYPE_IMPL2(cntrl)
__CTYPE_IMPL2(digit)
__CTYPE_IMPL2(graph)
__CTYPE_IMPL2(lower)
__CTYPE_IMPL2(print)
__CTYPE_IMPL2(punct)
__CTYPE_IMPL2(space)
__CTYPE_IMPL2(upper)
__CTYPE_IMPL2(xdigit)

int
isascii(int c)
{
	return ((unsigned int)c < 0x80);
}

int
toascii(int c)
{
	return (c & 0x7F);
}

int
tolower(int c)
{
	return (((c) >= 'A') && ((c) <= 'Z') ? (c) - 'A' + 'a' : (c));
}

int
toupper(int c)
{
	return (((c) >= 'a') && ((c) <= 'z') ? (c) - 'a' + 'A' : (c));
}

int
isbinry(int ch)
{
	uint8_t c = ch;
	return ((ch == 0x00) ||
	    (ch == 0xC0) || (ch == 0xC1) ||
	    ((ch >= 0xF0) && (ch <= 0xFF)));
}
