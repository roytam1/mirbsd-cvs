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
 */

#include <errno.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/mbrtowc.c,v 1.16 2008/08/01 23:37:37 tg Exp $");

size_t
mbrtowc(wchar_t *dst, const char *src, size_t len, mbstate_t *ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	wchar_t wc;
	size_t rv;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;
	if (__predict_false(dst == NULL))
		dst = &wc;

	if (__predict_false(src == NULL)) {
		ps->count = 0;
		return (0);
	}

	rv = optu8to16(dst, src, len, ps);
	if (*dst == 0)
		return (0);
	if (rv == 0) {
		errno = EILSEQ;
		return ((size_t)-1);
	}
	return (rv);
}
