#include <openssl/ripemd.h>

const char RMD160_version[] __attribute__((__used__)) = "$MirOS: src/lib/libssl/crypto/mbsd_ripemd160.c,v 1.1 2014/11/29 23:47:03 tg Exp $";

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
