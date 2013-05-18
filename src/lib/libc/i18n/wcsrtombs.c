/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2006, 2007
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

__RCSID("$MirOS: src/lib/libc/i18n/wcsrtombs.c,v 1.5 2007/02/02 19:28:34 tg Exp $");

#ifdef WCSNRTOMBS
size_t
wcsnrtombs(char *__restrict__ dst, const wchar_t **__restrict__ src,
    size_t max, size_t len, mbstate_t *__restrict__ ps)
#else
size_t
wcsrtombs(char *__restrict__ dst, const wchar_t **__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
#endif
{
	static mbstate_t internal_mbstate = { 0, 0 };	/* if ps == NULL */
	const wchar_t *s = *src;
	unsigned char *d = (unsigned char *)dst;
	wint_t wc;
	uint8_t count;

	/* make sure we can at least write one output byte */
	if ((dst != NULL) && (len == 0))
		return (0);

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	if ((count = ps->count)) {
		wc = ps->value;
		/* process remnants */
		goto process_state;
	}

 process_firstbyte:
	/* count is zero here; devour an input wide character */
#ifdef WCSNRTOMBS
	if (s >= (*src + max))
		goto empty_buf;
#endif
	wc = *s++;
	/* create the first output byte and state information from it */
	if (__predict_false(wc > WCHAR_MAX)) {
		errno = EILSEQ;
		return ((size_t)(-1));
	} else if (__predict_true(wc < 0x80)) {
		if (dst != NULL)
			*d = wc;
		/* count is already 0 */
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

#ifdef WCSNRTOMBS
 empty_buf:
#endif
	if (dst != NULL) {
		*src = s;
		/* save state information for restarting */
		ps->count = count;
		ps->value = wc;
	}
	return ((char *)d - dst);
}
