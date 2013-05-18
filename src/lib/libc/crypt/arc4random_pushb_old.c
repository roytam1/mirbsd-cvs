/*-
 * Copyright © 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * Implements legacy MirBSD API (deprecated but still useful for e.g.
 * configure checks that don’t match cpp macros).
 */

#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/crypt/arc4pushk.c,v 1.3 2010/09/12 17:10:51 tg Exp $");

#undef arc4random_push
#undef arc4random_pushb
#undef arc4random_pushk

void
arc4random_push(int n)
{
	arc4random_pushb_fast(&n, sizeof(n));
}

uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	arc4random_pushb_fast(buf, len);
	return (arc4random());
}

__weak_alias(arc4random_pushk, arc4random_pushb);
