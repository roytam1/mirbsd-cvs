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

const char SHA1_version[] = "$MirOS: src/lib/libssl/crypto/mbsd_sha1.c,v 1.3 2015/07/18 21:12:43 tg Exp $";
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

int
SHA224_Init(SHA256_CTX *context)
{
	context->state[0] = 0xc1059ed8UL;
	context->state[1] = 0x367cd507UL;
	context->state[2] = 0x3070dd17UL;
	context->state[3] = 0xf70e5939UL;
	context->state[4] = 0xffc00b31UL;
	context->state[5] = 0x68581511UL;
	context->state[6] = 0x64f98fa7UL;
	context->state[7] = 0xbefa4fa4UL;
	OPENSSL_cleanse(context->buffer, sizeof(context->buffer));
	context->bitcount = 0;
	return (1);
}

int
SHA224_Update(SHA256_CTX *c, const void *data, size_t len)
{
	return (SHA256_Update(c, data, len));
}

int
SHA224_Final(unsigned char digest[SHA224_DIGEST_LENGTH], SHA256_CTX *context)
{
	SHA256_Pad(context);

	if (digest != NULL) {
#if BYTE_ORDER != BIG_ENDIAN
		int i;

		for (i = 0; i < 7; i++) {
			digest[i * 4 + 0] = context->state[i] >> 24;
			digest[i * 4 + 1] = context->state[i] >> 16;
			digest[i * 4 + 2] = context->state[i] >> 8;
			digest[i * 4 + 3] = context->state[i];
		}
#else
		memcpy(digest, context->state, SHA224_DIGEST_LENGTH);
#endif
	}

	OPENSSL_cleanse(context, sizeof(SHA256_CTX));
	return (1);
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

	return (md);
}

unsigned char *
SHA224(const unsigned char *d, size_t n, unsigned char *md)
{
	SHA256_CTX ctx;

	if (!md)
		md = imd;
	SHA224_Init(&ctx);
	SHA256_Update(&ctx, d, n);
	SHA224_Final(md, &ctx);

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

	return (md);
}
#endif
