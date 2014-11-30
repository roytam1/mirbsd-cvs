/* $MirOS: src/lib/libssl/crypto/sha1.h,v 1.1 2014/11/29 23:47:04 tg Exp $ */

#ifndef HEADER_SHA1_H
#define HEADER_SHA1_H

#include <sys/types.h>
#include <sha1.h>
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
#define SHA_LBLOCK (SHA1_CBLOCK / 4)
#define SHA_LAST_BLOCK (SHA_CBLOCK - 8)
#define SHA_DIGEST_LENGTH SHA1_DIGEST_LENGTH

#define SHA_CTX SHA1_CTX

int SHA1_Init(SHA_CTX *c);
int SHA1_Update(SHA_CTX *c, const void *data, unsigned long len)
    __attribute__((__bounded__(__string__, 2, 3)));
int SHA1_Final(unsigned char *md, SHA_CTX *c)
    __attribute__((__bounded__(__minbytes__, 1, SHA1_DIGEST_LENGTH)));
void SHA1_Transform(SHA_CTX *c, const unsigned char *b)
    __attribute__((__bounded__(__minbytes__, 2, SHA1_BLOCK_LENGTH)));
unsigned char *SHA1(const unsigned char *d, unsigned long n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, SHA1_DIGEST_LENGTH)));

__END_DECLS

#endif
