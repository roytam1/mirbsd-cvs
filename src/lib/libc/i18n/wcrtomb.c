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

__RCSID("$MirOS: src/lib/libc/i18n/wcrtomb.c,v 1.16 2007/02/02 19:28:34 tg Exp $");

size_t
wcrtomb(char *__restrict__ dst, wchar_t wc, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	unsigned char *s = (unsigned char *)dst;
	uint8_t count;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	count = ps->count;

	if (__predict_false(dst == NULL)) {
		ps->count = 0;
		return (++count);
	}

	while (__predict_false(count)) {
		/* process any remnants from previous conversion state */
		*s++ = ((ps->value >> (6 * --count)) & 0x3F) | 0x80;
	}

	if (__predict_false(wc > WCHAR_MAX)) {
		errno = EILSEQ;
		return ((size_t)(-1));
	} else if (__predict_true(wc < 0x80)) {
		/* count is already 0 */
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
	return ((char *)s - dst);
}
