#include <openssl/ripemd.h>

#ifndef L_one
#undef RMD160_version
#undef RIPEMD160_Init
#undef RIPEMD160_Update
#undef RIPEMD160_Final
#undef RIPEMD160_Transform

const char RMD160_version[] __attribute__((__used__)) = "$MirOS: src/lib/libssl/crypto/mbsd_rmd160.c,v 1.1 2014/11/30 00:23:22 tg Exp $";

int
RIPEMD160_Init(RIPEMD160_CTX *c)
{
	RMD160Init(c);
	return (1);
}

int
RIPEMD160_Update(RIPEMD160_CTX *c, const void *data, unsigned long len)
{
	if (len)
		RMD160Update(c, data, len);
	return (1);
}

int
RIPEMD160_Final(unsigned char *md, RIPEMD160_CTX *c)
{
	RMD160Final(md, c);
	return (1);
}

void
RIPEMD160_Transform(RIPEMD160_CTX *c, const unsigned char *b)
{
	RMD160Transform(c->state, b);
}

#else

unsigned char *
RIPEMD160(const unsigned char *d, unsigned long n, unsigned char *md)
{
	static unsigned char imd[RIPEMD160_DIGEST_LENGTH];
	RIPEMD160_CTX ctx;

	if (!md)
		md = imd;
	RMD160Init(&ctx);
	if (n)
		RMD160Update(&ctx, d, n);
	RMD160Final(md, &ctx);

	return (md);
}
#endif
