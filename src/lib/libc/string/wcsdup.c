/* $MirOS: src/lib/libc/string/wcsdup.c,v 1.1 2006/06/01 21:54:47 tg Exp $ */

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
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/string/wcsdup.c,v 1.1 2006/06/01 21:54:47 tg Exp $");

wchar_t *
wcsdup(const wchar_t *s)
{
	size_t n;
	wchar_t *rv;

	n = wcslen(s) + 1;
	if ((rv = calloc(n, sizeof (wchar_t))) == NULL)
		return (NULL);
	memcpy(rv, s, n * sizeof (wchar_t));
	return (rv);
}
