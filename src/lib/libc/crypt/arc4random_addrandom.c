/*-
 * Copyright (c) 2010, 2014
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
 *-
 * Implementation of an old OpenBSD API with new arc4random(3).
 */

#include <syskern/libckern.h>
#include <stdlib.h>
#include "arc4random.h"
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random_addrandom.c,v 1.4 2014/03/29 10:25:53 tg Exp $");

void
arc4random_addrandom(u_char *dat, int datlen)
{
	_ARC4_LOCK();
	if (!a4state.a4s_initialised)
		arc4random_stir_locked(0);
	while (datlen >= 256) {
		arcfour_ksa(&a4state.cipher, dat, 256);
		datlen -= 256;
	}
	if (datlen)
		arcfour_ksa(&a4state.cipher, dat, datlen);
	_ARC4_UNLOCK();
}
__warn_references(arc4random_addrandom, "arc4random_addrandom got deprecated by OpenBSD, use arc4random_pushb_fast instead");
