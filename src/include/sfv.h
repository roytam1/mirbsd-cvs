/* $MirOS: src/include/tiger.h,v 1.1 2006/09/17 19:28:58 tg Exp $ */

#ifndef _SFV_H
#define _SFV_H

#define SFV_DIGEST_LENGTH		4
#define SFV_DIGEST_STRING_LENGTH	(SFV_DIGEST_LENGTH * 2 + 1)

typedef struct {
	uint64_t len;
	uint32_t crc;
} SFV_CTX;

#define SFV_DIGEST_UPPERCASE

#include <sys/cdefs.h>

__BEGIN_DECLS
void SFVInit(SFV_CTX *);
void SFVPad(SFV_CTX *);
void SFVUpdate(SFV_CTX *, const uint8_t *, size_t)
	__attribute__((bounded (string, 2, 3)));
void SFVFinal(uint8_t *, SFV_CTX *)
	__attribute__((bounded (minbytes, 1, SFV_DIGEST_LENGTH)));
char *SFVEnd(SFV_CTX *, char *)
	__attribute__((bounded (minbytes, 2, SFV_DIGEST_STRING_LENGTH)));
char *SFVFile(const char *, char *)
	__attribute__((bounded (minbytes, 2, SFV_DIGEST_STRING_LENGTH)));
char *SFVFileChunk(const char *, char *, off_t, off_t)
	__attribute__((bounded (minbytes, 2, SFV_DIGEST_STRING_LENGTH)));
char *SFVData(const uint8_t *, size_t, char *)
	__attribute__((bounded (string, 1, 2)))
	__attribute__((bounded (minbytes, 3, SFV_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif
