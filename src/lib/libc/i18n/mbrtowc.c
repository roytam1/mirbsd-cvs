/* $MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.6 2006/05/21 12:50:36 tg Exp $ */

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

__RCSID("$MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.6 2006/05/21 12:50:36 tg Exp $");

size_t __weak_mbrtowc(wchar_t *__restrict__, const char *__restrict__, size_t,
	    mbstate_t *__restrict__);
size_t
__weak_mbrtowc(wchar_t *__restrict__ pwc, const char *__restrict__ sb,
    size_t n, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)sb;
	wint_t c, w;
	size_t num;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if (__predict_false(sb == NULL)) {
		/* '\0' can only appear as first character */
		if (!__locale_is_utf8 || !ps->count)
			return (0);
 ilseq:
		errno = EILSEQ;
		return ((size_t)(-1));
	}

	if (__predict_false(!n--))
		goto not_enough;
	c = *s++;

	if (__predict_true(!__locale_is_utf8)) {
		if (__predict_false(c > MIR18N_SB_CVT))
			goto ilseq;
		goto one_char;
	}

	if (__predict_true(ps->count == 0)) {
		if (c < 0x80) {
 one_char:
			if (pwc != NULL)
				*pwc = c;
			return (c ? 1 : 0);
		} else if (c < 0xC2) {
			/* < 0xC0: spurious second byte */
			/* < 0xC2: would map to 0x80 */
			goto ilseq;
		} else if (c < 0xE0) {
			num = 1; /* one byte follows */
			w = (c & 0x1F) << 6;
		} else if (c < 0xF0) {
			num = 2; /* two bytes follow */
			w = (c & 0x0F) << 12;
		} else {
			/* we don't support more than UCS-2 */
			goto ilseq;
		}
	} else {
		num = ps->count;
		w = ps->value;
	}

 conv_byte:
	/* If there are no more bytes to inspect, make state */
	if (__predict_false(!n)) {
		ps->count = num;
		ps->value = w >> 6;
 not_enough:
		return ((size_t)(-2));
	}

	--n;
	if (((c = *s++) & 0xC0) != 0x80)
		goto ilseq;
	c &= 0x3F;

	w |= c << (6 * --num);

	if (__predict_true(!num)) {
		ps->count = 0;
		if (__predict_false(w > MIR18N_MB_MAX))
			goto ilseq;
		if (pwc != NULL)
			*pwc = w;
		return (s - (const unsigned char *)sb);
	}

	/* Check for non-minimalistic mapping encoding error in 3-byte seqs */
	if (__predict_false(w < 0x800))
		goto ilseq;
	else
		goto conv_byte;
}

__weak_alias(mbrtowc, __weak_mbrtowc);
