/**	$MirOS$ */
/*	$OpenBSD: md5.h,v 1.16 2004/06/22 01:57:30 jfb Exp $	*/

#ifndef _MD5_H_
#define _MD5_H_

#define	MD5_BLOCK_LENGTH		64
#define	MD5_DIGEST_LENGTH		16
#define	MD5_DIGEST_STRING_LENGTH	(MD5_DIGEST_LENGTH * 2 + 1)

typedef struct MD5Context {
	u_int32_t state[4];
	u_int64_t count;
	u_int8_t  buffer[MD5_BLOCK_LENGTH];
} MD5_CTX;

#include <sys/cdefs.h>

__BEGIN_DECLS
/* low-level MD5 functions from md5c.c */
void	MD5Init(MD5_CTX *);
void	MD5Update(MD5_CTX *, const u_int8_t *, size_t)
		__attribute__((__bounded__(__string__,2,3)));
void	MD5Pad(MD5_CTX *);
void	MD5Final(u_int8_t [MD5_DIGEST_LENGTH], MD5_CTX *)
		__attribute__((__bounded__(__minbytes__,1,MD5_DIGEST_LENGTH)));
void	MD5Transform(u_int32_t [4], const u_int8_t [MD5_BLOCK_LENGTH])
		__attribute__((__bounded__(__minbytes__,1,4)))
		__attribute__((__bounded__(__minbytes__,2,MD5_BLOCK_LENGTH)));

/* high-level functions from mdXhl.c */
char   *MD5End(MD5_CTX *, char *)
		__attribute__((__bounded__(__minbytes__,2,MD5_DIGEST_STRING_LENGTH)));
char   *MD5File(const char *, char *)
		__attribute__((__bounded__(__minbytes__,2,MD5_DIGEST_STRING_LENGTH)));
char   *MD5FileChunk(const char *, char *, off_t, off_t)
		__attribute__((__bounded__(__minbytes__,2,MD5_DIGEST_STRING_LENGTH)));
char   *MD5Data(const u_int8_t *, size_t, char *)
		__attribute__((__bounded__(__string__,1,2)))
		__attribute__((__bounded__(__minbytes__,3,MD5_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif	/* _MD5_H_ */
