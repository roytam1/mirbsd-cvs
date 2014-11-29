#include <string.h>
#include <openssl/crypto.h>

__RCSID("$MirOS: src/kern/c/explicit_bzero.c,v 1.2 2011/07/17 20:39:26 tg Exp $");

void
OPENSSL_cleanse(void *p, size_t n)
{
	bzero(p, n);
	/* protect from reordering */
	__asm __volatile("":::"memory");
}
