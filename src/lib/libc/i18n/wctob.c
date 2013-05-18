/* $MirOS: src/lib/libc/i18n/wctob.c,v 1.18 2007/02/02 21:06:23 tg Exp $ */

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

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/wctob.c,v 1.18 2007/02/02 21:06:23 tg Exp $");

#undef wctob
int
wctob(wint_t c)
{
	return (c > 0x7F ? EOF : (int)c);
}
