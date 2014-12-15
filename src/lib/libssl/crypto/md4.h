/* $MirOS: src/lib/libssl/crypto/md4.h,v 1.1 2014/11/29 23:47:04 tg Exp $ */

#ifndef HEADER_MD4_H
#define HEADER_MD4_H

#include <sys/types.h>
#include <md4.h>
#include <openssl/e_os2.h>

#ifdef OPENSSL_NO_MD4
#error MD4 is disabled.
#endif

__BEGIN_DECLS

#define MD4_LONG u_int32_t

#define MD4_CBLOCK MD4_BLOCK_LENGTH
#define MD4_LBLOCK (MD4_CBLOCK / 4)

int MD4_Init(MD4_CTX *c);
int MD4_Update(MD4_CTX *c, const void *data, unsigned long len)
    __attribute__((__bounded__(__string__, 2, 3)));
int MD4_Final(unsigned char *md, MD4_CTX *c)
    __attribute__((__bounded__(__minbytes__, 1, MD4_DIGEST_LENGTH)));
void MD4_Transform(MD4_CTX *c, const unsigned char *b)
    __attribute__((__bounded__(__minbytes__, 2, MD4_BLOCK_LENGTH)));
unsigned char *MD4(const unsigned char *d, unsigned long n, unsigned char *md)
    __attribute__((__bounded__(__string__, 1, 2)))
    __attribute__((__bounded__(__minbytes__, 3, MD4_DIGEST_LENGTH)));

#define MD4_version		"$MirOS$"
#define MD4_Init(c)		(MD4Init(c), 1)
#define MD4_Update(c,d,l)	(l ? (MD4Update(c, d, l), 1) : 1)
#define MD4_Final(md,c)		(MD4Final(md, c), 1)
#define MD4_Transform(c,b)	MD4Transform(((MD4_CTX *)(c))->state, b)

__END_DECLS

#endif
