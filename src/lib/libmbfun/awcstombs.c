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

__RCSID("$MirOS: src/lib/libc/i18n/awcstombs.c,v 1.1 2008/11/22 14:00:50 tg Exp $");

#ifdef L_awcsntombs
#define awcstombs	awcsntombs
#define namestr		"awcsntombs"
#define SECARG		, size_t n
#define wcsrtombs	wcsnrtombs
#define MAXARG		, n
#else
#define namestr		"awcstombs"
#define SECARG		/* nothing */
#define MAXARG		/* nothing */
#endif

char *
awcstombs(const wchar_t *ws  SECARG)
{
	char *s;
	size_t len;
	mbstate_t ps = { 0, 0 };

	if (!(s = malloc((len = wcsrtombs(NULL, &ws  MAXARG, 0, &ps) + 1))))
		err(1, "%s: out of memory allocating %zu bytes", namestr, len);
	len = wcsrtombs(s, &ws  MAXARG, len, &ps);
	s[len] = '\0';
	return (s);
}
