/* $MirOS: src/lib/libc/i18n/charsets.c,v 1.2 2005/09/22 21:24:47 tg Exp $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/charsets.c,v 1.2 2005/09/22 21:24:47 tg Exp $");

/* simple locale support (C and UTF-8) */

int locale_is_utf8 = 0;

char *
__weak_setlocale(int category, const char *locale)
{
	if ((category != LC_CTYPE) && (category != LC_ALL))
		return ("C");

	if (locale == NULL)
		return (locale_is_utf8 ? "en_US.UTF-8" : "C");

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

	if (strcasestr(locale, "UTF-8") || strcasestr(locale, "utf8")) {
		locale_is_utf8 = !0;
		return ("en_US.UTF-8");
	}

	locale_is_utf8 = 0;
	return ("C");
}

size_t
__mb_cur_max(void)
{
	return (locale_is_utf8 ? MB_LEN_MAX : 1);
}

__weak_alias(setlocale, __weak_setlocale);
