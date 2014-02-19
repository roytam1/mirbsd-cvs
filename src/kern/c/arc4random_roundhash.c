/*-
 * Copyright (c) 2010, 2011, 2012, 2013, 2014
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
#include <mirhash.h>

__RCSID("$MirOS: src/kern/c/arc4random_roundhash.c,v 1.9 2014/01/11 18:12:14 tg Exp $");

static void
arc4random_roundhash_do(uint32_t pools[32], unsigned int pool,
    const uint8_t *buf, size_t len)
{
	register uint32_t h;

	--pool;
	while (len--) {
		pool = (pool + 1) & 31;
		h = pools[pool];
		BAFHUpdateOctet_reg(h, *buf++);
		pools[pool] = h;
	}
}

static void
arc4random_roundhash_stir(uint32_t pools[32])
{
	register uint32_t h;
	uint32_t irest, ilow3, ihigh, j;
	union {
		uint32_t dw[32];
		uint8_t db[128];
	} tmpa;
	uint32_t tmpb[32];

	for (irest = 0; irest < 32; ++irest) {
		h = pools[irest];
		BAFHFinish_reg(h);
		tmpa.dw[irest] = h;
	}

	for (ihigh = 0; ihigh < 8; ihigh += 4)
		for (irest = 0; irest < 4; ++irest)
			for (ilow3 = 0; ilow3 < 4; ++ilow3) {
				j = ((ihigh + irest) << 4) + ilow3;
				h = tmpa.db[j] | (tmpa.db[j + 4] << 8) |
				    (tmpa.db[j + 8] << 16) |
				    (tmpa.db[j + 12] << 24);
				BAFHFinish_reg(h);
				pools[((ihigh + ilow3) << 2) + irest] = h;
				tmpb[(irest << 3) + ilow3 + (ihigh ^ 4)] = h;
			}

	arc4random_roundhash_do(pools, 0, (void *)tmpb, 128);
}

void
arc4random_roundhash(uint32_t pools[32], uint8_t *poolptr,
    const void *buf_, size_t len)
{
	size_t n, pool;
	const uint8_t *buf = (const uint8_t *)buf_;

	pool = *poolptr;
	goto chkpool;
 loop:
	n = 128 - pool;
	if (len < n)
		n = len;
	arc4random_roundhash_do(pools, pool, buf, n);
	buf += n;
	len -= n;
	pool += n;
 chkpool:
	if (pool > 127) {
		arc4random_roundhash_stir(pools);
		pool = 0;
	}
	if (len)
		goto loop;
	*poolptr = pool;
}
