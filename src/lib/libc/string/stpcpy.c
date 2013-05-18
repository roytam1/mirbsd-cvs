/*-
 * Copyright (c) 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
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

#define _GNU_SOURCE
#include <string.h>

__RCSID("$MirOS: src/lib/libc/string/stpcpy.c,v 1.2 2009/04/17 17:16:10 tg Exp $");

char *
stpcpy(char *dst, const char *src)
{
	size_t n;

	n = strlen(src);
	return ((char *)memcpy(dst, src, n + 1) + n);
}
