/* $MirOS: src/lib/libc/i18n/mbrlen.c,v 1.4 2007/02/02 21:06:21 tg Exp $ */

/*-
 * Copyright (c) 2006
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

#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/mbrlen.c,v 1.4 2007/02/02 21:06:21 tg Exp $");

size_t
mbrlen(const char *s, size_t n, mbstate_t *ps)
{
	static mbstate_t internal = { 0, 0 };

	return (mbrtowc(NULL, s, n, (ps == NULL) ? &internal : ps));
}
