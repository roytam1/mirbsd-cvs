/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <errno.h>
#include <locale.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/wctob.c,v 1.3 2005/09/22 21:52:28 tg Exp $");

size_t
wcrtomb(char *__restrict__ sb, wchar_t wc, mbstate_t *__restrict__ ps)
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

	if (__predict_true(!locale_is_utf8)) {
		if (wc < 0x0100) {
			*sb = wc;
			return (1);
		}
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
