/* $MirOS: src/bin/md5/suma.h,v 1.2 2005/04/12 20:52:21 tg Exp $ */

#define	ADLER32_DIGEST_LENGTH		4
#define	ADLER32_DIGEST_STRING_LENGTH	(ADLER32_DIGEST_LENGTH * 2 + 1)

typedef uint32_t ADLER32_CTX;

void ADLER32_Init(ADLER32_CTX *);
void ADLER32_Update(ADLER32_CTX *, const uint8_t *, size_t)
    __attribute__((__bounded__(__string__,2,3)));
char *ADLER32_End(ADLER32_CTX *, char *)
    __attribute__((__bounded__(__minbytes__,2,ADLER32_DIGEST_STRING_LENGTH)));
