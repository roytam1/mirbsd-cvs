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
 */

#include <err.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/ambstowcs.c,v 1.2 2008/11/22 14:00:50 tg Exp $");

#ifdef L_ambsntowcs
#define ambstowcs	ambsntowcs
#define namestr		"ambsntowcs"
#define SECARG		, size_t n
#define mbsrtowcs	mbsnrtowcs
#define MAXARG		, n
#else
#define namestr		"ambstowcs"
#define SECARG		/* nothing */
#define MAXARG		/* nothing */
#endif

wchar_t *
ambstowcs(const char *s  SECARG)
{
	wchar_t *ws;
	size_t len;
	mbstate_t ps = { 0, 0 };

	if ((ws = calloc((len = mbsrtowcs(NULL, &s  MAXARG, 0, &ps) + 1),
	    sizeof (wchar_t))) == NULL)
		err(1, "%s: out of memory allocating %zu wide characters",
		    namestr, len);
	len = mbsrtowcs(ws, &s  MAXARG, len, &ps);
	ws[len] = L'\0';
	return (ws);
}
