/* $MirOS$ */

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

#define mir18n_attributes
#include "mir18n.h"

__RCSID("$MirOS$ for TYPE type");

int
iswTYPE(wint_t wc)
{
	unsigned char attributes;

	if (!__locale_is_utf8)
		return ((wc <= MIR18N_SB_MAX) ? isTYPE(wc) : 0);

	if (__predict_false(wc > MIR18N_MB_MAX))
		return (0);

	attributes = attribute_table[wc >> 8][wc & 0xFF];
	return (((attributes & wmask_incl(wctype_TYPE)) != 0) &&
	    ((attributes & wmask_excl(wctype_TYPE)) == 0));
}
