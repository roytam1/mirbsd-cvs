/* $MirOS: contrib/code/Snippets/setlocale.c,v 1.2 2007/06/07 12:30:37 tg Exp $ */

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

#define setlocale donotdeclareme

#include <sys/types.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#undef setlocale

static const char __rcsid_1[] = "$miros: src/lib/libc/i18n/charsets.c,v 1.17 2007/06/07 16:41:04 tg Exp $";
static const char __rcsid_2[] = "$MirOS: contrib/code/Snippets/setlocale.c,v 1.2 2007/06/07 12:30:37 tg Exp $";

/* simple locale support (C and UTF-8) */

char *setlocale(int, const char *);

static bool locale_is_utf8 = false;

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
	strlcpy(lc_ctype, locale_is_utf8 ? STR_UTF : STR_C, sizeof (lc_ctype));
	return (lc_ctype);
}
