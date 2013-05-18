/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

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
#include <sys/localedef.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdlib.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/charsets.c,v 1.14 2006/09/07 17:13:15 tg Exp $");

const char *__weak_setlocale(int, const char *);

const char *
__weak_setlocale(int category, const char *locale __attribute__((unused)))
{
	return ((category == LC_CTYPE) || (category == LC_ALL) ?
	    "en_US.UTF-8" : "C");
}

__weak_alias(setlocale, __weak_setlocale);
