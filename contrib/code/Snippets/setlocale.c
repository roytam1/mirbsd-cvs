/* $MirOS: contrib/code/Snippets/setlocale.c,v 1.1 2007/01/18 22:07:22 tg Exp $ */

/*-
 * Copyright (c) 2005, 2007
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

#include <sys/types.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

static const char __rcsid_1[] = "$miros: src/lib/libc/i18n/charsets.c,v 1.14 2006/09/07 17:13:15 tg Exp $";
static const char __rcsid_2[] = "$MirOS: contrib/code/Snippets/setlocale.c,v 1.1 2007/01/18 22:07:22 tg Exp $";

/* simple locale support (C and UTF-8) */

char *setlocale(int, const char *);

static bool locale_is_utf8 = false;

char *
setlocale(int category, const char *locale)
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

	locale_is_utf8 = (strcasestr(locale, "UTF-8")
	    || strcasestr(locale, "utf8"));

 getlocale:
	return ((char *)(locale_is_utf8 ? "en_US.UTF-8" : "C"));
}
