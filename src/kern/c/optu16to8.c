/*-
 * Copyright (c) 2008
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
 *-
 * Note: this only works because OPTU is the *only* available locale.
 */

#include <libckern.h>
#ifdef _KERN_HOSTED
#include <errno.h>
#endif

__RCSID("$MirOS: src/kern/c/optu16to8.c,v 1.2 2008/11/22 09:02:33 tg Exp $");

#ifdef _KERN_HOSTED
static size_t _optu16to8(uint8_t *, wchar_t, mbstate_t *);

size_t
wcrtomb(char *s, wchar_t wc, mbstate_t *ps)
{
	static mbstate_t w_state = { 0, 0 };

	return (_optu16to8((uint8_t *)s, wc, ps ? ps : &w_state));
}
#endif

size_t
optu16to8(char *s, wchar_t wc, mbstate_t *ps)
{
	static mbstate_t o_state = { 0, 0 };

#ifdef _KERN_HOSTED
	return (_optu16to8((uint8_t *)s, wc, ps ? ps : &o_state));
}

static size_t
_optu16to8(uint8_t *s, wchar_t wc, mbstate_t *ps)
{
#endif
	uint8_t count, *src = (uint8_t *)s;

#ifndef _KERN_HOSTED
	if (__predict_false(ps == NULL))
		ps = &o_state;
#endif

	if ((count = ps->count) == 3) {
#ifdef _KERN_HOSTED
		errno = EINVAL;
#endif
		return ((size_t)(-1));
	}

	if (__predict_false(s == NULL)) {
		ps->count = 0;
		return (count + 1);
	}

	while (__predict_false(count)) {
		/* process any remnants from previous conversion state */
		*s++ = ((ps->value >> (6 * --count)) & 0x3F) | 0x80;
	}

	if (__predict_false(wc > WCHAR_MAX)) {
#ifdef _KERN_HOSTED
		errno = EILSEQ;
#endif
		return ((size_t)(-1));
	} else if (__predict_true(wc < 0x80 || iswoctet(wc))) {
		/* count is already 0 */
		*s++ = wc & 0xFF;
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
	return ((size_t)((uint8_t *)s - src));
}
