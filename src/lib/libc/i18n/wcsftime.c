/* $MirOS: src/lib/libc/i18n/wcsftime.c,v 1.1 2006/06/02 12:53:17 tg Exp $ */

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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * stub only
 */

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/wcsftime.c,v 1.1 2006/06/02 12:53:17 tg Exp $");

size_t	__weak_wcsftime(wchar_t *__restrict__, size_t,
    const wchar_t *__restrict__, const struct tm *__restrict__);
size_t
__weak_wcsftime(wchar_t *__restrict__ wcs, size_t maxsize,
    const wchar_t *__restrict__ format, const struct tm *__restrict__ tp)
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
