/* $MirOS: src/include/suma.h,v 1.1 2007/05/07 15:21:18 tg Exp $ */

#ifndef _SUMA_H
#define _SUMA_H

#define SUMA_DIGEST_LENGTH		4
#define SUMA_DIGEST_STRING_LENGTH	(SUMA_DIGEST_LENGTH * 2 + 1)

typedef uint32_t SUMA_CTX;

#define SUMA_DIGEST_UPPERCASE

#include <sys/cdefs.h>

__BEGIN_DECLS
void SUMAInit(SUMA_CTX *);
void SUMAPad(SUMA_CTX *);
void SUMAUpdate(SUMA_CTX *, const uint8_t *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void SUMAFinal(uint8_t *, SUMA_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, SUMA_DIGEST_LENGTH)));
char *SUMAEnd(SUMA_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAFile(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAFileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAData(const uint8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, SUMA_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
