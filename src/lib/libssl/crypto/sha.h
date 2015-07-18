/* $MirOS: src/lib/libssl/crypto/sha.h,v 1.3 2015/07/18 21:12:43 tg Exp $ */

#ifndef HEADER_SHA1_H
#define HEADER_SHA1_H

#include <sys/types.h>
#include <sha1.h>
#include <sha2.h>
#include <openssl/e_os2.h>

#ifdef OPENSSL_NO_SHA
#error SHA is disabled.
#endif

#ifdef OPENSSL_NO_SHA1
#error SHA1 is disabled.
#endif

__BEGIN_DECLS

#define SHA_LONG u_int32_t

#define SHA_CBLOCK SHA1_BLOCK_LENGTH
#define SHA_LBLOCK 16
#define SHA_LAST_BLOCK (SHA_CBLOCK - 8)
#define SHA_DIGEST_LENGTH SHA1_DIGEST_LENGTH

#define SHA256_CBLOCK (SHA_LBLOCK * 4)
#define SHA512_CBLOCK (SHA_LBLOCK * 8)
#define SHA224_DIGEST_LENGTH 28

#define SHA_CTX SHA1_CTX

int SHA1_Init(SHA_CTX *c);
int SHA1_Update(SHA_CTX *c, const void *data, size_t len)
    __attribute__((__bounded__(__string__, 2, 3)));
int SHA1_Final(unsigned char *md, SHA_CTX *c)
    __attribute__((__bounded__(__minbytes__, 1, SHA1_DIGEST_LENGTH)));
void SHA1_Transform(SHA_CTX *c, const unsigned char *b)
    __attribute__((__bounded__(__minbytes__, 2, SHA1_BLOCK_LENGTH)));
unsigned char *SHA1(const unsigned char *d, size_t n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA1_DIGEST_LENGTH)));

#define SHA1_version		"$MirOS: src/lib/libssl/crypto/sha.h,v 1.3 2015/07/18 21:12:43 tg Exp $"
#define SHA256_version		SHA1_version
#define SHA512_version		SHA1_version
#define SHA1_Init(c)		(SHA1Init(c), 1)
#define SHA1_Update(c,d,l)	(l ? (SHA1Update(c, d, l), 1) : 1)
#define SHA1_Final(md,c)	(SHA1Final(md, c), 1)
#define SHA1_Transform(c,b)	SHA1Transform(((SHA_CTX *)(c))->state, b)

int SHA224_Init(SHA256_CTX *c);
int SHA224_Update(SHA256_CTX *c, const void *data, size_t len)
    __attribute__((__bounded__(__string__, 2, 3)));
int SHA224_Final(unsigned char *md, SHA256_CTX *c)
    __attribute__((__bounded__(__minbytes__, 1, SHA224_DIGEST_LENGTH)));
unsigned char *SHA224(const unsigned char *d, size_t n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA224_DIGEST_LENGTH)));

unsigned char *SHA256(const unsigned char *d, size_t n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA256_DIGEST_LENGTH)));
unsigned char *SHA384(const unsigned char *d, size_t n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA384_DIGEST_LENGTH)));
unsigned char *SHA512(const unsigned char *d, size_t n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA512_DIGEST_LENGTH)));

__END_DECLS

#endif
