/* $MirOS: contrib/code/libhaible/towlower.c,v 1.9 2006/06/01 21:39:01 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Based upon code written by Bruno Haible for GNU libutf8:
 * Copyright (c) 1999, 2000, 2001
 *	Free Software Foundation, Inc.
 *
 * This work is licenced under the terms of the GNU Library General
 * Public License, Version 2, as in /usr/share/doc/legal/COPYING.LIB-2
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <wctype.h>

#define mir18n_caseconv
#include "mir18n.h"

__RCSID("$MirOS: contrib/code/libhaible/towlower.c,v 1.9 2006/06/01 21:39:01 tg Exp $");

wint_t
towlower(wint_t x)
{
	if (!__locale_is_utf8)
		return ((x <= MIR18N_SB_MAX) ? (wint_t)tolower(x) : x);
	else
		return ((x <= MIR18N_MB_MAX) ?
		    (x + tolower_table[x >> 8][x & 0xff]) : x);
}
