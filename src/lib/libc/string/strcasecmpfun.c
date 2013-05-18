/* $MirOS: src/lib/libc/string/strcasecmpfun.c,v 1.2 2006/11/21 02:38:32 tg Exp $ */

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
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#if defined(WCSCASECMP)
#define WIDEC 1
#elif defined(WCSNCASECMP)
#define WIDEC 1
#else
#define WIDEC 0
#endif

#if WIDEC
#include <wctype.h>
#define CHAR		wchar_t
#define	LC		L
#define x_tolower	towlower
#define strcasecmp	wcscasecmp
#define strncasecmp	wcsncasecmp
#else
#include <ctype.h>
#include <string.h>
#define	CHAR		char
#define	LC		/* nothing */
#define	x_tolower	_tolower
#endif

__RCSID("$MirOS: src/lib/libc/string/strcasecmpfun.c,v 1.2 2006/11/21 02:38:32 tg Exp $");

#if defined(STRCASECMP) || defined(WCSCASECMP)
int
strcasecmp(const CHAR *s1, const CHAR *s2)
{
	while (x_tolower(*s1) == x_tolower(*s2))
		if (*s1++ == LC '\0')
			return (0);
		else
			s2++;
	return (x_tolower(*s1) - x_tolower(*s2));
}
#endif

#if defined(STRNCASECMP) || defined(WCSNCASECMP)
int
strncasecmp(const CHAR *s1, const CHAR *s2, size_t n)
{
	while (n--) {
		if (x_tolower(*s1) != x_tolower(*s2))
			return (x_tolower(*s1) - x_tolower(*s2));
		if (*s1++ == LC '\0')
			break;
		s2++;
	}
	return (0);
}
#endif
