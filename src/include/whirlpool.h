/* $MirOS: src/include/whirlpool.h,v 1.1 2007/05/07 14:06:07 tg Exp $ */

#ifndef _WHIRLPOOL_H
#define _WHIRLPOOL_H

#define WHIRLPOOL_BLOCK_LENGTH		64
#define WHIRLPOOL_DIGEST_LENGTH		64
#define WHIRLPOOL_DIGEST_STRING_LENGTH	(WHIRLPOOL_DIGEST_LENGTH * 2 + 1)

typedef struct {
	uint8_t bitLength[32];	/* number of hashed bits (256-bit counter) */
	uint8_t buffer[WHIRLPOOL_BLOCK_LENGTH];	/* buffer of data to hash */
	int bufferBits;		/* current number of bits on the buffer */
	int bufferPos;		/* current (possibly incomplete) byte slot */
	uint64_t hash[WHIRLPOOL_DIGEST_LENGTH / 8];	/* the hashing state */
} WHIRLPOOL_CTX;

#include <sys/cdefs.h>

__BEGIN_DECLS
void WHIRLPOOLInit(WHIRLPOOL_CTX *);
void WHIRLPOOLPad(WHIRLPOOL_CTX *);
void WHIRLPOOLUpdate(WHIRLPOOL_CTX *, const uint8_t *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void WHIRLPOOLFinal(uint8_t *, WHIRLPOOL_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, WHIRLPOOL_DIGEST_LENGTH)));
char *WHIRLPOOLEnd(WHIRLPOOL_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, WHIRLPOOL_DIGEST_STRING_LENGTH)));
char *WHIRLPOOLFile(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, WHIRLPOOL_DIGEST_STRING_LENGTH)));
char *WHIRLPOOLFileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, WHIRLPOOL_DIGEST_STRING_LENGTH)));
char *WHIRLPOOLData(const uint8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, WHIRLPOOL_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
