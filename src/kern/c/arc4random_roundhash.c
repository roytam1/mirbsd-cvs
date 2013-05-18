/*-
 * Copyright (c) 2010
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

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

void
arc4random_roundhash(uint32_t pools[32], uint8_t *poolptr,
    const void *buf_, size_t len)
{
	register uint32_t h;
	register uint8_t pool;
	const uint8_t *buf = (const uint8_t *)buf_;

	pool = *poolptr;
	while (len--) {
		h = pools[pool];
		h += *buf++;
		h += h << 10;
		h ^= h >> 6;
		pools[pool] = h;
		pool = (pool + 1) & 31;
	}
	*poolptr = pool;
}
