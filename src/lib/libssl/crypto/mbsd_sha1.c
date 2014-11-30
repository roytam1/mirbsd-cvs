#include <openssl/sha.h>

const char SHA1_version[] __attribute__((__used__)) = "$MirOS: src/lib/libssl/crypto/mbsd_sha1.c,v 1.1 2014/11/29 23:47:03 tg Exp $";

int
SHA1_Init(SHA_CTX *c)
{
	SHA1Init(c);
	return (1);
}

int
SHA1_Update(SHA_CTX *c, const void *data, unsigned long len)
{
	if (len)
		SHA1Update(c, data, len);
	return (1);
}

int
SHA1_Final(unsigned char *md, SHA_CTX *c)
{
	SHA1Final(md, c);
	return (1);
}

void
SHA1_Transform(SHA_CTX *c, const unsigned char *b)
{
	SHA1Transform(c->state, b);
}

unsigned char *
SHA1(const unsigned char *d, unsigned long n, unsigned char *md)
{
	static unsigned char imd[SHA1_DIGEST_LENGTH];
	SHA_CTX ctx;

	if (!md)
		md = imd;
	SHA1Init(&ctx);
	if (n)
		SHA1Update(&ctx, d, n);
	SHA1Final(md, &ctx);

	return (md);
}
