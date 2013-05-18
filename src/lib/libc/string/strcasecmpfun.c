/* $MirOS: src/lib/libc/string/strcasecmpfun.c,v 1.5 2007/02/02 17:43:55 tg Exp $ */

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

#undef c_size
#undef c_wide
#ifdef WCSNCASECMP
#define c_size
#define c_wide
#endif
#ifdef WCSCASECMP
#define c_wide
#endif
#ifdef STRNCASECMP
#define c_size
#endif

#ifdef c_wide
#include <wctype.h>
#define CHAR		wchar_t
#define	LC(x)		L ## x
#define x_tolower	towlower
#define strcasecmp	wcscasecmp
#define strncasecmp	wcsncasecmp
#else
#include <ctype.h>
#include <string.h>
#define	CHAR		char
#define	LC(x)		x
#define	x_tolower	tolower
#endif

__RCSID("$MirOS: src/lib/libc/string/strcasecmpfun.c,v 1.5 2007/02/02 17:43:55 tg Exp $");

#ifndef c_size
int
strcasecmp(const CHAR *s1, const CHAR *s2)
{
	while (x_tolower(*s1) == x_tolower(*s2))
		if (*s1++ == LC('\0'))
			return (0);
		else
			s2++;
	return (x_tolower(*s1) - x_tolower(*s2));
}
#else
int
strncasecmp(const CHAR *s1, const CHAR *s2, size_t n)
{
	while (n--) {
		if (x_tolower(*s1) != x_tolower(*s2))
			return (x_tolower(*s1) - x_tolower(*s2));
		if (*s1++ == LC('\0'))
			break;
		s2++;
	}
	return (0);
}
#endif
