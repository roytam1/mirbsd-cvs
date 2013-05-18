/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

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

__RCSID("$MirOS: src/lib/libc/gen/isctype.c,v 1.4 2006/11/03 01:21:49 tg Exp $");

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

#if MIR18N_C_CSET == 2
#define CTYPE_NUM_CHARS       256
__IDSTRING(CTYPE_NUM_CHARS, "ctype ('C' locale) handles 8 bits");
#else
#define CTYPE_NUM_CHARS       128
__IDSTRING(CTYPE_NUM_CHARS, "ctype ('C' locale) handles 7 bits");
#endif

#define __CTYPE_IMPL(t,v)						     \
	int is ## t (int c)						     \
	{								     \
		if ((c < 0) || (c >= v))				     \
			return (0);					     \
		return ((__C_attribute_table_pg[c] & (_ctp_ ## t & 0xFF)) && \
		    !(__C_attribute_table_pg[c] & (_ctp_ ## t >> 8)));	     \
	}

__CTYPE_IMPL(alnum,128)
__CTYPE_IMPL(alpha,128)
__CTYPE_IMPL(blank,128)
__CTYPE_IMPL(cntrl,CTYPE_NUM_CHARS)
__CTYPE_IMPL(digit,128)
__CTYPE_IMPL(graph,128)
__CTYPE_IMPL(lower,128)
__CTYPE_IMPL(print,CTYPE_NUM_CHARS)
__CTYPE_IMPL(punct,128)
__CTYPE_IMPL(space,128)
__CTYPE_IMPL(upper,128)
__CTYPE_IMPL(xdigit,128)

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
