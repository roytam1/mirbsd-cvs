/*-
 * Copyright © 2015
 *	mirabilos <tg@mirbsd.org>
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
 */

#include <openssl/crypto.h>
#include <openssl/sha.h>

#ifndef L_one
#undef SHA1_version
#undef SHA256_version
#undef SHA512_version
#undef SHA1_Init
#undef SHA1_Update
#undef SHA1_Final
#undef SHA1_Transform

const char SHA1_version[] = "$MirOS: src/lib/libssl/crypto/mbsd_sha1.c,v 1.2 2014/12/15 21:04:21 tg Exp $";
const char *SHA256_version = SHA1_version;
const char *SHA512_version = SHA1_version;

int
SHA1_Init(SHA_CTX *c)
{
	SHA1Init(c);
	return (1);
}

int
SHA1_Update(SHA_CTX *c, const void *data, size_t len)
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

#else

__RCSID(SHA1_version);

static unsigned char imd[SHA512_DIGEST_LENGTH];

unsigned char *
SHA1(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA_CTX ctx;

	if (!md)
		md = imd;
	SHA1Init(&ctx);
	if (n)
		SHA1Update(&ctx, d, n);
	SHA1Final(md, &ctx);
	OPENSSL_cleanse(&ctx, sizeof(ctx));

	return (md);
}

unsigned char *
SHA256(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA256_CTX ctx;

	if (!md)
		md = imd;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, d, n);
	SHA256_Final(md, &ctx);
	OPENSSL_cleanse(&ctx, sizeof(ctx));

	return (md);
}

unsigned char *
SHA384(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA384_CTX ctx;

	if (!md)
		md = imd;
	SHA384_Init(&ctx);
	SHA384_Update(&ctx, d, n);
	SHA384_Final(md, &ctx);
	OPENSSL_cleanse(&ctx, sizeof(ctx));

	return (md);
}

unsigned char *
SHA512(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA512_CTX ctx;

	if (!md)
		md = imd;
	SHA512_Init(&ctx);
	SHA512_Update(&ctx, d, n);
	SHA512_Final(md, &ctx);
	OPENSSL_cleanse(&ctx, sizeof(ctx));

	return (md);
}
#endif
