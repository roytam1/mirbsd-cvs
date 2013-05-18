/*-
 * Copyright (c) 2010, 2011, 2012
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
#include <nzat.h>

__RCSID("$MirOS: src/kern/c/arc4random_roundhash.c,v 1.3 2011/07/06 22:22:07 tg Exp $");

void
arc4random_roundhash(uint32_t pools[32], uint8_t *poolptr,
    const void *buf_, size_t len)
{
	register uint32_t h;
	register unsigned int pool;
	const uint8_t *buf = (const uint8_t *)buf_;

	pool = *poolptr;
	while (len--) {
		pool = (pool + 1) & 31;
		h = pools[pool];
		NZATUpdateByte(h, *buf++);
		pools[pool] = h;
	}
	*poolptr = pool;
}
