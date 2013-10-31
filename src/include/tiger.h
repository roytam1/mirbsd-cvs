/* $MirOS: src/include/tiger.h,v 1.1 2006/09/17 19:28:58 tg Exp $ */

#ifndef _TIGER_H
#define _TIGER_H

#define TIGER_BLOCK_LENGTH		64
#define TIGER_DIGEST_LENGTH		24
#define TIGER_DIGEST_STRING_LENGTH	(TIGER_DIGEST_LENGTH * 2 + 1)

typedef struct {
	uint64_t digest[3];
	uint64_t count;
	uint8_t buffer[TIGER_BLOCK_LENGTH];
} TIGER_CTX;

#include <sys/cdefs.h>

__BEGIN_DECLS
void TIGERInit(TIGER_CTX *);
void TIGERPad(TIGER_CTX *);
void TIGERTransform(uint64_t *, const uint8_t *)
	__attribute__((__bounded__(__minbytes__, 1, 24)))
	__attribute__((__bounded__(__minbytes__, 2, TIGER_BLOCK_LENGTH)));
void TIGERUpdate(TIGER_CTX *, const uint8_t *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void TIGERFinal(uint8_t *, TIGER_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, TIGER_DIGEST_LENGTH)));
char *TIGEREnd(TIGER_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, TIGER_DIGEST_STRING_LENGTH)));
char *TIGERFile(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, TIGER_DIGEST_STRING_LENGTH)));
char *TIGERFileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, TIGER_DIGEST_STRING_LENGTH)));
char *TIGERData(const uint8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, TIGER_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
