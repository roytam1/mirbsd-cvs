/* $MirOS: src/lib/libc/gen/isctype.c,v 1.5 2007/02/02 17:53:57 tg Exp $ */

/*-
 * Copyright (c) 2006
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
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/gen/isctype.c,v 1.5 2007/02/02 17:53:57 tg Exp $");

#undef isalnum
#undef isalpha
#undef isascii
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

#define __CTYPE_IMPL(t)							     \
	int is ## t (int c)						     \
	{								     \
		if ((c < 0) || (c >= 128))				     \
			return (0);					     \
		return ((__C_attribute_table_pg[c] & (_ctp_ ## t & 0xFF)) && \
		    !(__C_attribute_table_pg[c] & (_ctp_ ## t >> 8)));	     \
	}

__CTYPE_IMPL(alnum)
__CTYPE_IMPL(alpha)
__CTYPE_IMPL(blank)
__CTYPE_IMPL(cntrl)
__CTYPE_IMPL(digit)
__CTYPE_IMPL(graph)
__CTYPE_IMPL(lower)
__CTYPE_IMPL(print)
__CTYPE_IMPL(punct)
__CTYPE_IMPL(space)
__CTYPE_IMPL(upper)
__CTYPE_IMPL(xdigit)

int
isascii(int c)
{
	return ((unsigned int)c <= 0177);
}

int
toascii(int c)
{
	return (c & 0177);
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
