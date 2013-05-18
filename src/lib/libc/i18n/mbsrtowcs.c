/* $MirOS: src/lib/libc/i18n/mbsrtowcs.c,v 1.6 2006/11/19 22:05:11 tg Exp $ */

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

#include <errno.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/mbsrtowcs.c,v 1.6 2006/11/19 22:05:11 tg Exp $");

#ifdef MBSNRTOWCS
size_t
mbsnrtowcs(wchar_t *__restrict__ dst, const char **__restrict__ src,
    size_t max, size_t len, mbstate_t *__restrict__ ps)
#else
size_t
mbsrtowcs(wchar_t *__restrict__ dst, const char **__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
#endif
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)(*src);
	wchar_t *d = dst;
	wint_t c, wc;
	unsigned count;

	/* make sure we can at least write one output wide character */
	if ((dst != NULL) && (len == 0))
		return (0);

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if ((count = __locale_is_utf8 ? ps->count : 0)) {
		wc = ps->value << 6;
		goto conv_state;
	}

 conv_first:
#ifdef MBSNRTOWCS
	if (s >= (*(const unsigned char **)src + max)) {
		/* wc is unimportant here since count == 0 */
 empty_buf:
		if (dst != NULL) {
			/* ps is only updated if we really write! */
			ps->count = count;
			ps->value = wc >> 6;
			*src = (const char *)s;
		}
		return (d - dst);
	}
#endif
	wc = *s++;
	if (__predict_true(!__locale_is_utf8 || (wc < 0x80))) {
		if (__predict_false(wc > MIR18N_SB_CVT)) {
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
#ifdef MBSNRTOWCS
		if (s >= (*(const unsigned char **)src + max))
			goto empty_buf;	/* here, we store wc and count */
#endif
		if (((c = *s++) & 0xC0) != 0x80)
			goto ilseq;
		c &= 0x3F;
		wc |= c << (6 * --count);

		/* Check for non-minimalistic mapping error in 3-byte seqs */
		if (__predict_false(count && (wc < 0x0800)))
			goto ilseq;
	}

	if (__predict_false(wc > MIR18N_MB_MAX))
		goto ilseq;

	if (dst != NULL)
		*d = wc;
	if (wc != L'\0') {
		++d;
		if ((dst == NULL) || (--len))
			goto conv_first;
	} else
		s = NULL;

	if (dst != NULL) {
		*src = (const char *)s;
		ps->count = 0;
	}
	return (d - dst);
}
