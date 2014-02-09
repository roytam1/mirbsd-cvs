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

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/mbsrtowcs.c,v 1.13 2008/11/22 11:23:22 tg Exp $");

#ifdef MBSNRTOWCSVIS
#undef mbsnrtowcs
#undef optu8to16
#define mbsnrtowcs mbsnrtowcsvis
#define optu8to16 optu8to16vis
#define MBSNRTOWCS
#endif

#ifdef MBSNRTOWCS
size_t
mbsnrtowcs(wchar_t *pwcs, const char **s, size_t max, size_t n, mbstate_t *ps)
#else
#define max MB_CUR_MAX
size_t
mbsrtowcs(wchar_t *pwcs, const char **s, size_t n, mbstate_t *ps)
#endif
{
	static mbstate_t internal_mbstate = { 0, 0 };
	size_t rv = 0, fr;
	wchar_t wc;
	const char * src = *s;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

#ifdef MBSNRTOWCS
	if (!max) {
		while (!pwcs || n) {
			if (optu8to16(&wc, NULL, 0, ps) != 0)
				break;
			if (pwcs)
				*pwcs++ = wc;
			++rv;
			--n;
		}
		goto done;
	}
#endif

 loop:
#ifdef MBSNRTOWCS
	if (!max)
		goto done;
#endif
	if (pwcs && !n)
		goto done;
	if ((fr = optu8to16(&wc, src, max, ps)) == (size_t)-2) {
		src += max;
		goto done;
	}
	/* fr == (size_t)-1 can never happen */
	src += fr;
#ifdef MBSNRTOWCS
	max -= fr;
#endif
	if (pwcs)
		*pwcs++ = wc;
	++rv;
	--n;
	if (wc)
		goto loop;
	src = NULL;
	--rv;

 done:
	if (pwcs)
		*s = src;
	return (rv);
}
