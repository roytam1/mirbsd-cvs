/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2005, 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <errno.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.14 2007/02/02 19:28:33 tg Exp $");

size_t
mbrtowc(wchar_t *__restrict__ dst, const char *__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)src;
	wint_t c, wc;
	uint8_t count;

	if (__predict_false(!len))
		return ((size_t)(-2));

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if (__predict_false(src == NULL)) {
		ps->count = 0;
		return (0);
	}

	if ((count = ps->count)) {
		wc = ps->value << 6;
		goto conv_state;
	}

	--len;
	wc = *s++;
	if (__predict_true(wc < 0x80)) {
		/* count == 0 already */
		;
	} else if (__predict_false(wc < 0xC2)) {
		/* < 0xC0: spurious second byte */
		/* < 0xC2: non-minimalistic mapping error in 2-byte seqs */
 ilseq:
		errno = EILSEQ;
		return ((size_t)(-1));
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
