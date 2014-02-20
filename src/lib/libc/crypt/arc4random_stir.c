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
 */

#include <syskern/libckern.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arc4random.h"
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random_stir.c,v 1.2 2014/02/19 21:16:28 tg Exp $");

void
arc4random_stir(void)
{
	_ARC4_LOCK();
	arc4random_stir_locked(0);
	_ARC4_UNLOCK();
}
__warn_references(arc4random_stir, "arc4random_stir got deprecated by OpenBSD");
