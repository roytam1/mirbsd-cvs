/* $MirOS: src/include/tiger.h,v 1.1 2006/09/17 19:28:58 tg Exp $ */

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
	__attribute__((bounded (string, 2, 3)));
void SUMAFinal(uint8_t *, SUMA_CTX *)
	__attribute__((bounded (minbytes, 1, SUMA_DIGEST_LENGTH)));
char *SUMAEnd(SUMA_CTX *, char *)
	__attribute__((bounded (minbytes, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAFile(const char *, char *)
	__attribute__((bounded (minbytes, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAFileChunk(const char *, char *, off_t, off_t)
	__attribute__((bounded (minbytes, 2, SUMA_DIGEST_STRING_LENGTH)));
char *SUMAData(const uint8_t *, size_t, char *)
	__attribute__((bounded (string, 1, 2)))
	__attribute__((bounded (minbytes, 3, SUMA_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
