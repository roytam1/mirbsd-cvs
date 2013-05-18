/* $MirOS: src/lib/libc/i18n/charsets.c,v 1.15 2007/02/02 21:06:20 tg Exp $ */

/*-
 * Copyright (c) 2007
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

__RCSID("$MirOS: src/lib/libc/i18n/charsets.c,v 1.15 2007/02/02 21:06:20 tg Exp $");

#define STR_C	"C"
#define STR_UTF	"en_US.UTF-8"

char *
setlocale(int category, const char *locale __attribute__((unused)))
{
	static char lc_other[] = STR_C;
	static char lc_ctype[] = STR_UTF;

	if ((category != LC_CTYPE) && (category != LC_ALL)) {
		memmove(lc_other, STR_C, sizeof (lc_other));
		return (lc_other);
	}

	memmove(lc_ctype, STR_UTF, sizeof (lc_ctype));
	return (lc_ctype);
}

#ifdef __weak_alias
__weak_alias(setlocale, __weak_setlocale);
#endif
