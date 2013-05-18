/*
 * Implement a legacy (deprecated) MirBSD ABI.
 * The API is still available as arc4random_pushk macro.
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/taitime.h>
#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/crypt/arc4pushk.c,v 1.2 2008/12/27 21:17:54 tg Exp $");

/* to go away with the next libc major bump */

#undef arc4random_pushk
uint32_t arc4random_pushk(const void *, size_t);

uint32_t
arc4random_pushk(const void *buf, size_t len)
{
	return (arc4random_pushb(buf, len));
}

#undef arc4random_push
void
arc4random_push(int n)
{
	arc4random_pushb_fast(&n, sizeof(n));
}

#undef arc4random_pushb
uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	arc4random_pushb_fast(buf, len);
	return (arc4random());
}
