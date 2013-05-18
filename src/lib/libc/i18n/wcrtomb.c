/* $MirOS: src/lib/libc/i18n/wcrtomb.c,v 1.5 2006/05/21 12:30:47 tg Exp $ */

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

#include <errno.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/wcrtomb.c,v 1.5 2006/05/21 12:30:47 tg Exp $");

size_t __weak_wcrtomb(char *__restrict__, wchar_t, mbstate_t *__restrict__);

size_t
__weak_wcrtomb(char *__restrict__ sb, wchar_t wc, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	unsigned char *s = (unsigned char *)sb;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if (__predict_false(s == NULL)) {
		size_t numb = ps->count;
		ps->count = 0;
		return (numb + 1);
	}

	if (__predict_true(!__locale_is_utf8)) {
		if (wc < 0x0100) {
			*sb = wc;
			return (1);
		}
 ilseq:
		errno = EILSEQ;
		return ((size_t)(-1));
	}

	if (__predict_false(ps->count > 0)) {
		/* process remnants from an earlier conversion state */
		wc = ps->value;
		goto do_conv;
	}

	if (wc < 0x0080) {
		*s++ = wc;
	} else if (wc < 0x0800) {
		ps->count = 1;
		*s++ = (wc >> 6) | 0xC0;
	} else if (__predict_false(wc > 0xFFFD)) {
		goto ilseq;
	} else {
		ps->count = 2;
		*s++ = (wc >> 12) | 0xE0;
	}

 do_conv:
	while (ps->count) {
		*s++ = ((wc >> (6 * --ps->count)) & 0x3F) | 0x80;
	}
	return (s - (unsigned char *)sb + 1);
}

__weak_alias(wcrtomb, __weak_wcrtomb);
