/*-
 * Copyright (c) 2007, 2011, 2014
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

#include <sys/param.h>
#include <stdlib.h>
#ifdef WIDEC
#include <wchar.h>
#else
#include <string.h>
#endif

__RCSID("$MirOS: src/lib/libc/string/strndup.c,v 1.5 2011/07/01 19:17:26 tg Exp $");

#ifdef WIDEC
#define strndup	wcsndup
#define strlen	wcslen
#define char_t	wchar_t
#define NUL	L'\0'
#else
#define char_t	char
#define NUL	'\0'
#endif

char_t *
strndup(const char_t *s, size_t max)
{
	register size_t n;
	char_t *cp;

	n = strnlen(s, max);
	if ((cp = calloc(n + 1, sizeof(char_t))) != NULL) {
		memcpy(cp, s, n * sizeof(char_t));
		cp[n] = NUL;
	}
	return (cp);
}
