/* $MirOS: src/lib/libc/i18n/charsets.c,v 1.12 2006/06/03 22:12:55 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdlib.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/charsets.c,v 1.12 2006/06/03 22:12:55 tg Exp $");

/* simple locale support (C and UTF-8) */

const char *__weak_setlocale(int, const char *);

bool __locale_is_utf8 = false;

const char *
__weak_setlocale(int category, const char *locale)
{
	if ((category != LC_CTYPE) && (category != LC_ALL))
		return ("C");

	if (locale == NULL)
		goto getlocale;

	if (*locale == '\0') {
		locale = getenv("LC_ALL");
		if (!locale || !*locale) {
			locale = getenv("LC_CTYPE");
			if (!locale || !*locale)
				locale = getenv("LANG");
			if (!locale)
				locale = "C";
		}
	}

	__locale_is_utf8 = (strcasestr(locale, "UTF-8")
	    || strcasestr(locale, "utf8"));

 getlocale:
	return (__locale_is_utf8 ? "en_US.UTF-8" : "C");
}

__weak_alias(setlocale, __weak_setlocale);
