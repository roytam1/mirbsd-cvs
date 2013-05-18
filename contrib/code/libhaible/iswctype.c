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

__RCSID("$MirOS$");

int
iswctype(wint_t wc, wctype_t desc)
{
	unsigned char attributes;

	if (!__locale_is_utf8) {
		if (wc < MIR18N_SB_MAX)
			switch (wmask_number(desc)) {
			case wmask_number(wctype_alnum):
				return (isalnum(wc));
			case wmask_number(wctype_alpha):
				return (isalpha(wc));
			case wmask_number(wctype_blank):
				return (isblank(wc));
			case wmask_number(wctype_cntrl):
				return (iscntrl(wc));
			case wmask_number(wctype_digit):
				return (isdigit(wc));
			case wmask_number(wctype_graph):
				return (isgraph(wc));
			case wmask_number(wctype_lower):
				return (islower(wc));
			case wmask_number(wctype_print):
				return (isprint(wc));
			case wmask_number(wctype_punct):
				return (ispunct(wc));
			case wmask_number(wctype_space):
				return (isspace(wc));
			case wmask_number(wctype_upper):
				return (isupper(wc));
			case wmask_number(wctype_xdigit):
				return (isxdigit(wc));
			}
		return (0);
	}

	if (__predict_false(wc > MIR18N_MB_MAX))
		return (0);

	attributes = attribute_table[wc >> 8][wc & 0xFF];
	return (((attributes & wmask_incl(desc)) != 0) &&
	    ((attributes & wmask_excl(desc)) == 0));
}
