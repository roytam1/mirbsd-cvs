/* $MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.13 2006/11/01 20:01:19 tg Exp $ */

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
 */

#include <errno.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.13 2006/11/01 20:01:19 tg Exp $");

size_t
mbrtowc(wchar_t *__restrict__ dst, const char *__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)src;
	wint_t c, wc;
	unsigned count;

	if (__predict_false(!len))
		return ((size_t)(-2));

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if (__predict_false(src == NULL)) {
		ps->count = 0;
		return (0);
	}

	if ((count = __locale_is_utf8 ? ps->count : 0)) {
		wc = ps->value << 6;
		goto conv_state;
	}

	--len;
	wc = *s++;
	if (__predict_true(!__locale_is_utf8 || (wc < 0x80))) {
		if (__predict_false(wc > 0x7F)) {
 ilseq:
			errno = EILSEQ;
			return ((size_t)(-1));
		}
		/* count == 0 already */
	} else if (wc < 0xC2) {
		/* < 0xC0: spurious second byte */
		/* < 0xC2: non-minimalistic mapping error in 2-byte seqs */
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
	while (__predict_false(count)) {
		/* If there are no more bytes to inspect, make state */
		if (__predict_false(!len)) {
			ps->count = count;
			ps->value = wc >> 6;
			return ((size_t)(-2));
		}

		--len;
		if (((c = *s++) & 0xC0) != 0x80)
			goto ilseq;
		c &= 0x3F;
		wc |= c << (6 * --count);

		/* Check for non-minimalistic mapping error in 3-byte seqs */
		if (__predict_false(count && (wc < 0x0800)))
			goto ilseq;
	}

	if (__predict_false(wc > WCHAR_MAX))
		goto ilseq;

	if (dst != NULL)
		*dst = wc;
	ps->count = 0;
	return (wc ? ((const char *)s - src) : 0);
}
