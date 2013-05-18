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

#include <libckern.h>

__RCSID("$MirOS: src/kern/c/strcmp.c,v 1.2 2008/08/03 21:02:00 tg Exp $");

#ifdef WIDEC
#define NUL L'\0'
int
wcscmp(const wchar_t *cp1, const wchar_t *cp2)
{
#else
#define NUL '\0'
int
strcmp(const char *s1, const char *s2)
{
	const uint8_t *cp1 = s1, *cp2 = s2;
#endif
	while (*cp1 == *cp2++)
		if (*cp1++ == NUL)
			return (0);
	return (*cp1 - *--cp2);
}

#ifdef lint
#ifdef WIDEC
int
wcscoll(const wchar_t *cp1, const wchar_t *cp2)
{
	return (wcscmp(cp1, cp2));
}
#else
int
strcoll(const char *s1, const char *s2)
{
	return (strcmp(s1, s2));
}
#endif
#else /* lint */
#ifdef WIDEC
__strong_alias(wcscoll, wcscmp);
#else
__strong_alias(strcoll, strcmp);
#endif
#endif /* lint */
