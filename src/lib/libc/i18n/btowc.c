/* $MirOS: src/lib/libc/i18n/btowc.c,v 1.7 2006/05/21 12:38:39 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/btowc.c,v 1.7 2006/05/21 12:38:39 tg Exp $");

wint_t __weak_btowc(int);

wint_t
__weak_btowc(int c)
{
	return (((c >= 0) && (c <= (_locale_is_utf8 ? 0x7E : 0xFF)))
	    ? (wchar_t)c : WEOF);
}

__weak_alias(btowc, __weak_btowc);
