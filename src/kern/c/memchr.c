/*-
 * Copyright (c) 2008
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

#include <libckern.h>

__RCSID("$MirOS: src/kern/c/memchr.c,v 1.1 2008/08/01 18:09:17 tg Exp $");

void *
memchr(const void *b, int c, size_t len)
{
	const uint8_t *cp = b;

	while (len--)
		if (*cp++ == (uint8_t)c)
			/* const broken by BAD API */
			return ((void *)(cp - 1));
	return (NULL);
}
