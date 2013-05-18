/* $MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.9 2006/06/02 19:45:00 tg Exp $ */

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

__RCSID("$MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.9 2006/06/02 19:45:00 tg Exp $");

size_t
mbrtowc(wchar_t *__restrict__ pwc, const char *__restrict__ src,
    size_t n, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)src;
	wint_t c, wc, wc_max;
	unsigned count;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if (__predict_false(src == NULL)) {
		ps->count = 0;
		return (0);
	}

	if (__predict_false(!n))
		return ((size_t)(-2));

	wc_max = __locale_is_utf8 ? MIR18N_MB_MAX : MIR18N_SB_CVT;

	if ((count = __locale_is_utf8 ? ps->count : 0)) {
		wc = ps->value << 6;
		goto conv_state;
	}

	--n;
	wc = *s++;
	if (__predict_true(!__locale_is_utf8 || (wc < 0x80))) {
		if (__predict_false(wc > MIR18N_SB_CVT)) {
 ilseq:
			errno = EILSEQ;
			return ((size_t)(-1));
		}
		if (pwc != NULL)
			*pwc = wc;
		return (wc ? 1 : 0);
	} else if (wc < 0xC2) {
		/* < 0xC0: spurious second byte */
		/* < 0xC2: would map to 0x80 */
		goto ilseq;
	} else if (wc < 0xE0) {
		count = 1; /* one byte follows */
		wc = (wc & 0x1F) << 6;
	} else if (wc < 0xF0) {
		count = 2; /* two bytes follow */
		wc = (wc & 0x0F) << 12;
	} else {
		/* we don't support more than UCS-2 */
		goto ilseq;
	}

 conv_state:
	/* If there are no more bytes to inspect, make state */
	if (__predict_false(!n)) {
		ps->count = count;
		ps->value = wc >> 6;
		return ((size_t)(-2));
	}

	--n;
	if (((c = *s++) & 0xC0) != 0x80)
		goto ilseq;
	c &= 0x3F;
	wc |= c << (6 * --count);

	if (__predict_false(count)) {
		/* Check for non-minimalistic mapping
		 * encoding error in 3-byte sequences */
		if (__predict_false(wc < 0x800))
			goto ilseq;
		else
			goto conv_state;
	}

	if (__predict_false(wc > MIR18N_MB_MAX))
		goto ilseq;

	if (pwc != NULL)
		*pwc = wc;
	ps->count = 0;
	return ((const char *)s - src);
}
