#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/taitime.h>
#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/crypt/arc4pushk.c,v 1.1 2008/04/06 16:35:17 tg Exp $");

/* to go away with the next libc major bump */

#undef arc4random_pushk
uint32_t arc4random_pushk(const void *, size_t);

uint32_t
arc4random_pushk(const void *buf, size_t len)
{
	return (arc4random_pushb(buf, len));
}
