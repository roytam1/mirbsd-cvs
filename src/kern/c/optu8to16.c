/*-
 * Copyright (c) 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *
 * The author reserves the right to steward the OPTU encoding forms.
 */

#include <libckern.h>

__RCSID("$MirOS: src/kern/c/optu8to16.c,v 1.2 2008/08/02 00:10:01 tg Exp $");

size_t
optu8to16(wchar_t * restrict pwc, const char * restrict src, size_t n,
    mbstate_t * restrict ps)
{
	static mbstate_t istate = { 0, 0 };
	const unsigned char *s = (const unsigned char *)src;
	wint_t c, wc;
	uint8_t count;

	if (__predict_false(ps == NULL))
		ps = &istate;

	if (__predict_false((count = ps->count) == 3)) {
		if (pwc != NULL && (n == 0 || s != NULL))
			*pwc = 0xEF80 | (ps->value & 0x3F);
		ps->count = 0;
		return (0);
	}

	if (__predict_false(n == 0)) {
		if (__predict_true(count == 0))
			return ((size_t)(-2));
		wc = ps->value << 6;
		goto dismiss;
	}

	if (__predict_false(s == NULL)) {
		ps->count = 0;
		return (0);
	}

	if (__predict_false(count)) {
		wc = ps->value << 6;
		goto conv_state;
	}

	--n;
	wc = *s++;
	if (__predict_true(wc < 0x80)) {
		/* count == 0 already */
		;
	} else if (__predict_false(wc < 0xC2 || wc >= 0xF0)) {
		/* count == 0 already */
		wc |= 0xEF00;
	} else if (wc < 0xE0) {
		count = 1; /* one byte follows */
		wc = (wc & 0x1F) << 6;
	} else /* (wc < 0xF0) */ {
		count = 2; /* two bytes follow */
		wc = (wc & 0x0F) << 12;
	}

 conv_state:
	while (__predict_false(count)) {
		/* if there are no more bytes to inspect, make state */
		if (__predict_false(n-- == 0)) {
			ps->count = count;
			ps->value = wc >> 6;
			return ((size_t)(-2));
		}

		/*
		 * check for invalid CESU-8 encoding: not a trail byte (ASCII,
		 * lead byte, or outside BMP lead), non-minimalistic encoding,
		 * reserved OPTU encoding range (XXX shouldnt EINVAL mbrtowc),
		 * or value larger than WCHAR_MAX (U+FFFD = EF BF BD)
		 */
		if (__predict_false((((c = *s++) & 0xC0) != 0x80) ||
		    (count == 2 && wc == 0 && c < 0xA0) ||
		    (count == 2 && wc == 0xE000 && c > 0xBD) ||
		    (count == 1 && wc == 0xFFC0 && c > 0xBD))) {
			/* reject current octet, dismiss former octet */
			s--;
 dismiss:
			if (count == 2) {
				count = 0;
				wc = (wc >> 12) | 0xEFE0;
			} else if (wc < 0x0800) {
				count = 0;
				wc = (wc >> 6) | 0xEFC0;
			} else {
				ps->value = (wc >> 6) /* & 0x3F */;
				count = 3;
				wc = (wc >> 12) | 0xEFE0;
			}
			break;
		}
		wc |= (c & 0x3F) << (6 * --count);
	}
	ps->count = count;
	if (pwc != NULL)
		*pwc = wc;
	return ((size_t)((const char *)s - src));
}
