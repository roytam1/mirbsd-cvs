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
 *-
 * XXX remove this file some time when bumping libc major anyway
 */

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/i18n/mbcurmax.c,v 1.9 2007/02/02 19:28:33 tg Exp $");

bool __locale_is_utf8 = true;

int __mb_cur_max(void);

int
__mb_cur_max(void)
{
	return (MB_CUR_MAX);
}
