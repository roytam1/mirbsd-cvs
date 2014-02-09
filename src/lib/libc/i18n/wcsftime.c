/* $MirOS: src/lib/libc/i18n/wcsftime.c,v 1.4 2007/02/02 21:06:22 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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
 *-
 * stub only
 */

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/wcsftime.c,v 1.4 2007/02/02 21:06:22 tg Exp $");

size_t __weak_wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm *);

size_t
__weak_wcsftime(wchar_t *wcs, size_t maxsize, const wchar_t *format,
    const struct tm *tp)
{
	mbstate_t state = { 0, 0 };
	const wchar_t *wfmt = format;
	char *fmt, *res;
	const char **resp;
	size_t i;

	if ((res = calloc(maxsize, MB_LEN_MAX)) == NULL)
		return (0);

	i = wcsrtombs(NULL, &wfmt, 0, &state);
	if (i == (size_t)-1) {
		free(res);
		return (0);
	}
	if ((fmt = malloc(++i)) == NULL) {
		free(res);
		return (0);
	}
	wcsrtombs(fmt, &wfmt, i, &state);
	bzero(&state, sizeof (mbstate_t));

	if (strftime(res, maxsize * MB_LEN_MAX, fmt, tp) == 0) {
		free(res);
		free(fmt);
		return (0);
	}

	free(fmt);
	resp = (const char **)&res;
	i = mbsrtowcs(wcs, resp, maxsize, &state);
	free(res);
	if (i == (size_t)-1)
		return (0);
	return ((*resp == NULL) ? i : 0);
}

__weak_alias(wcsftime, __weak_wcsftime);
