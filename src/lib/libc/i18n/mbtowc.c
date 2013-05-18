/* $MirOS: src/lib/libc/i18n/mbtowc.c,v 1.1 2006/06/01 22:17:20 tg Exp $ */

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
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

__RCSID("$MirOS: src/lib/libc/i18n/mbtowc.c,v 1.1 2006/06/01 22:17:20 tg Exp $");

int
mbtowc(wchar_t *__restrict__ pwc, const char *__restrict__ s, size_t n)
{
	mbstate_t state = { 0, 0 };
	int rv;

	return (((rv = mbrtowc(pwc, s, n, &state)) < 0) ? -1 : rv);
}
