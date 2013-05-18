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

#include <sys/types.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arc4random.h"
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random_pushb.c,v 1.1 2010/09/12 17:10:53 tg Exp $");

void
arc4random_pushb_fast(const void *buf, size_t len)
{
	struct {
		struct timespec tp;
		const void *dp, *sp;
		size_t sz;
	} pbuf;

	clock_gettime(CLOCK_MONOTONIC, &pbuf.tp);
	pbuf.dp = buf;
	pbuf.sp = &pbuf;
	pbuf.sz = len;

	_ARC4_LOCK();
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr,
	    &pbuf, sizeof(pbuf));
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr, buf, len);
	_ARC4_UNLOCK();
}
