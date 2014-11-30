/* $MirOS: src/lib/libssl/crypto/ripemd160.h,v 1.1 2014/11/29 23:47:04 tg Exp $ */

#ifndef HEADER_RIPEMD160_H
#define HEADER_RIPEMD160_H

#include <sys/types.h>
#include <rmd160.h>
#include <openssl/e_os2.h>

#ifdef OPENSSL_NO_RIPEMD
#error RMD160 is disabled.
#endif

__BEGIN_DECLS

#define RIPEMD160_LONG u_int32_t

#define RIPEMD160_CBLOCK RMD160_BLOCK_LENGTH
#define RIPEMD160_LBLOCK (RIPEMD160_CBLOCK / 4)
#define RIPEMD160_DIGEST_LENGTH RMD160_DIGEST_LENGTH

#define RIPEMD160_CTX RMD160_CTX

int RIPEMD160_Init(RIPEMD160_CTX *c);
int RIPEMD160_Update(RIPEMD160_CTX *c, const void *data, unsigned long len)
    __attribute__((__bounded__(__string__, 2, 3)));
int RIPEMD160_Final(unsigned char *md, RIPEMD160_CTX *c)
    __attribute__((__bounded__(__minbytes__, 1, RIPEMD160_DIGEST_LENGTH)));
void RIPEMD160_Transform(RIPEMD160_CTX *c, const unsigned char *b)
    __attribute__((__bounded__(__minbytes__, 2, RMD160_BLOCK_LENGTH)));
unsigned char *RIPEMD160(const unsigned char *d, unsigned long n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, RIPEMD160_DIGEST_LENGTH)));

__END_DECLS

#endif
