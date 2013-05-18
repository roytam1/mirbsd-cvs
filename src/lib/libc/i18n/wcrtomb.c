/* $MirOS: src/lib/libc/i18n/wcrtomb.c,v 1.12 2006/10/27 15:52:28 tg Exp $ */

/*-
 * Copyright (c) 2005, 2006
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
 *-
 * THIS FUNCTION VIOLATES THE INTERFACE DEFINITION!
 * If the 'ps' argument contains a conversion state, at maximum, five
 * bytes (two from the 'ps', three (= MB_CUR_MAX) from the 'wc' argu-
 * ment) are stored. We changed MB_LEN_MAX and MB_CUR_MAX on 20061027
 * to accomodate this fact.
 */

#include <errno.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/wcrtomb.c,v 1.12 2006/10/27 15:52:28 tg Exp $");

size_t
wcrtomb(char *__restrict__ src, wchar_t wc, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	unsigned char *s = (unsigned char *)src;
	unsigned count;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	count = __locale_is_utf8 ? ps->count : 0;

	if (__predict_false(src == NULL)) {
		ps->count = 0;
		return (++count);
	}

	while (__predict_false(count)) {
		/* process any remnants from previous conversion state */
		*s++ = ((ps->value >> (6 * --count)) & 0x3F) | 0x80;
	}

	if (__predict_false(wc >
	    (__locale_is_utf8 ? MIR18N_MB_MAX : MIR18N_SB_CVT))) {
		errno = EILSEQ;
		return ((size_t)(-1));
	} else if (__predict_true((wc < 0x80) || !__locale_is_utf8)) {
		*s++ = wc;
	} else if (wc < 0x0800) {
		count = 1;
		*s++ = (wc >> 6) | 0xC0;
	} else {
		count = 2;
		*s++ = (wc >> 12) | 0xE0;
	}

	while (__predict_false(count)) {
		*s++ = ((wc >> (6 * --count)) & 0x3F) | 0x80;
	}
	ps->count = 0;
	return ((char *)s - src);
}
