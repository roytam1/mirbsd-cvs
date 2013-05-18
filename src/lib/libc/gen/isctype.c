/* $MirOS: src/lib/libc/gen/isctype.c,v 1.3 2006/11/02 13:36:32 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#define _ANSI_LIBRARY
#include <ctype.h>
#include <stdio.h>
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/gen/isctype.c,v 1.3 2006/11/02 13:36:32 tg Exp $");

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
