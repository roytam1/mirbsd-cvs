/*-
 * Copyright (c) 2007, 2010
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
 */

#include <sys/param.h>

#ifdef __weak_alias
#define setlocale __weak_setlocale
#endif

#include <sys/localedef.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdlib.h>
#include <string.h>

__RCSID("$MirOS: src/lib/libc/i18n/charsets.c,v 1.17 2007/06/07 16:41:04 tg Exp $");

#undef _tolower
#define _tolower(c)	((c) | 0x20)

#define STR_C	"C"
#define STR_UTF	"en_US.UTF-8"

char *
setlocale(int category, const char *locale)
{
	static char lc_other[] = STR_C;
	static char lc_ctype[] = STR_UTF;

	if ((category != LC_CTYPE) && (category != LC_ALL)) {
		memmove(lc_other, STR_C, sizeof (lc_other));
		return (lc_other);
	}

	if (locale) {
		/* try to be somewhat POSIX conformant */
		while (*locale && *locale != '.')
			++locale;
		if (*locale++) {
			if (_tolower(*locale++) != 'u')
				return (NULL);
			if (_tolower(*locale++) != 't')
				return (NULL);
			if (_tolower(*locale++) != 'f')
				return (NULL);
			if (*locale == '-')
				++locale;
			if (*locale++ != '8')
				return (NULL);
			if (*locale && *locale != '@')
				return (NULL);
			/* "*.UTF-8" or "*.UTF-8@*" */
		} /* else "*([!.])" */
	}

	memmove(lc_ctype, STR_UTF, sizeof (lc_ctype));
	return (lc_ctype);
}

#undef setlocale

#ifdef __weak_alias
__weak_alias(setlocale, __weak_setlocale);
#endif
