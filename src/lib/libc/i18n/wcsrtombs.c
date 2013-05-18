/* $MirOS: src/lib/libc/i18n/wcsrtombs.c,v 1.2 2006/06/03 13:25:06 tg Exp $ */

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

__RCSID("$MirOS: src/lib/libc/i18n/wcsrtombs.c,v 1.2 2006/06/03 13:25:06 tg Exp $");

size_t
wcsrtombs(char *__restrict__ dst, const wchar_t **__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };	/* if ps == NULL */
	const wchar_t *s = *src;
	unsigned char *d = (unsigned char *)dst;
	wint_t wc, wc_max;
	unsigned count;

	/* make sure we can at least write one output byte */
	if ((dst != NULL) && (len == 0))
		return (0);

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	/* highest allowed wide character to convert */
	wc_max = __locale_is_utf8 ? MIR18N_MB_MAX : MIR18N_SB_CVT;

	/* in the 'C' locale, the mbstate information is ignored */
	if ((count = __locale_is_utf8 ? ps->count : 0)) {
		wc = ps->value;
		/* process remnants */
		goto process_state;
	}

 process_firstbyte:
	/* count is zero here; devour an input wide character */
	wc = *s++;
	/* create the first output byte and state information from it */
	if (__predict_false(wc > wc_max)) {
		errno = EILSEQ;
		return ((size_t)(-1));
	} else if (__predict_true((wc < 0x80) || !__locale_is_utf8)) {
		if (dst != NULL)
			*d = wc;
	} else if (wc < 0x0800) {
		if (dst != NULL)
			*d = (wc >> 6) | 0xC0;
		count = 1;
	} else {
		if (dst != NULL)
			*d = (wc >> 12) | 0xE0;
		count = 2;
	}
	/* account the output byte, except if it's the terminating NUL */
	if (wc > 0)
		++d;
	/* at this point, we have written an output byte */
	--len;

 process_state:
	/* entering with len >= 0, count + wc containing state info */
	while (__predict_false((count > 0) && ((len > 0) || (dst == NULL)))) {
		--count;
		if (dst != NULL)
			*d = ((wc >> (6 * count)) & 0x3F) | 0x80;
		++d;
		--len;
	}

	/* here: either len == 0 or count == 0 (or both!) */
	if (__predict_false(wc == 0))
		/* last character was a terminating NUL, count == 0 */
		s = NULL;
	else if (__predict_true(count == 0))
		/* so, if there's still output space left or we ignore it */
		if ((len > 0) || (dst == NULL))
			/* loop on to the next full input wide character */
			goto process_firstbyte;

	if (dst != NULL) {
		*src = s;
		/* save state information for restarting */
		ps->count = count;
		ps->value = wc;
	}
	return ((char *)d - dst);
}
