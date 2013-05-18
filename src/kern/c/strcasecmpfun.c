/*-
 * Copyright (c) 2006, 2007, 2010
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

#include <sys/types.h>
#include <libckern.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

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
#define	CHAR		char
#define	LC(x)		x
#define x_tolower(c)	__extension__({			\
	int __CKERN_Tl = (c);				\
							\
	(__CKERN_Tl >= 'A') && (__CKERN_Tl <= 'Z') ?	\
	    __CKERN_Tl - 'A' + 'a' : __CKERN_Tl;	\
})
#endif

__RCSID("$MirOS: src/lib/libc/string/strcasecmpfun.c,v 1.6 2007/08/08 20:57:41 tg Exp $");

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
