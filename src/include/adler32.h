/* $MirOS: src/include/suma.h,v 1.1 2007/05/07 15:21:18 tg Exp $ */

#ifndef _ADLER32_H
#define _ADLER32_H

#define ADLER32_DIGEST_LENGTH		4
#define ADLER32_DIGEST_STRING_LENGTH	(ADLER32_DIGEST_LENGTH * 2 + 1)

typedef uint32_t ADLER32_CTX;

#define ADLER32_DIGEST_UPPERCASE

#include <sys/cdefs.h>

__BEGIN_DECLS
void ADLER32Init(ADLER32_CTX *);
void ADLER32Update(ADLER32_CTX *, const uint8_t *, size_t)
	__attribute__((bounded (string, 2, 3)));
void ADLER32Final(uint8_t *, ADLER32_CTX *)
	__attribute__((bounded (minbytes, 1, ADLER32_DIGEST_LENGTH)));
char *ADLER32End(ADLER32_CTX *, char *)
	__attribute__((bounded (minbytes, 2, ADLER32_DIGEST_STRING_LENGTH)));
char *ADLER32File(const char *, char *)
	__attribute__((bounded (minbytes, 2, ADLER32_DIGEST_STRING_LENGTH)));
char *ADLER32FileChunk(const char *, char *, off_t, off_t)
	__attribute__((bounded (minbytes, 2, ADLER32_DIGEST_STRING_LENGTH)));
char *ADLER32Data(const uint8_t *, size_t, char *)
	__attribute__((bounded (string, 1, 2)))
	__attribute__((bounded (minbytes, 3, ADLER32_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
