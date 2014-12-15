#include <openssl/md4.h>

#ifndef L_one
#undef MD4_version
#undef MD4_Init
#undef MD4_Update
#undef MD4_Final
#undef MD4_Transform

const char MD4_version[] __attribute__((__used__)) = "$MirOS: src/lib/libssl/crypto/mbsd_md4.c,v 1.1 2014/11/29 23:47:03 tg Exp $";

int
MD4_Init(MD4_CTX *c)
{
	MD4Init(c);
	return (1);
}

int
MD4_Update(MD4_CTX *c, const void *data, unsigned long len)
{
	if (len)
		MD4Update(c, data, len);
	return (1);
}

int
MD4_Final(unsigned char *md, MD4_CTX *c)
{
	MD4Final(md, c);
	return (1);
}

void
MD4_Transform(MD4_CTX *c, const unsigned char *b)
{
	MD4Transform(c->state, b);
}

#else

unsigned char *
MD4(const unsigned char *d, unsigned long n, unsigned char *md)
{
	static unsigned char imd[MD4_DIGEST_LENGTH];
	MD4_CTX ctx;

	if (!md)
		md = imd;
	MD4Init(&ctx);
	if (n)
		MD4Update(&ctx, d, n);
	MD4Final(md, &ctx);

	return (md);
}
#endif
