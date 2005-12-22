/* $MirOS: src/bin/md5/suma.h,v 1.1 2005/03/16 17:19:06 tg Exp $ */

#define	SUMA_DIGEST_LENGTH		4
#define	SUMA_DIGEST_STRING_LENGTH	(SUMA_DIGEST_LENGTH * 2 + 1)

typedef u_int32_t SUMA_CTX;

void SUMA_Init(SUMA_CTX *);
void SUMA_Update(SUMA_CTX *, const u_int8_t *, size_t)
    __attribute__((__bounded__(__string__,2,3)));
void SUMA_Final(SUMA_CTX *);
char *SUMA_End(SUMA_CTX *, char *)
    __attribute__((__bounded__(__minbytes__,2,SUMA_DIGEST_STRING_LENGTH)));
