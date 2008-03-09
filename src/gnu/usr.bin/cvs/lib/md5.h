/* $MirOS$ */

#ifndef	MD5_H
#define	MD5_H

#include "/usr/include/md5.h"

/* ridiculous. */

#define	/* struct */ md5_ctx		/* struct */ MD5Context

#define	md5_init_ctx			MD5Init
#define	md5_process_bytes(buf,len,ctx)	MD5Update(ctx,buf,len)
#define	md5_finish_ctx(ctx,md)		MD5Final(md,ctx)

/* one up */

char *md5_buffer(const u_int8_t *, size_t, char *)
		__attribute__((__bounded__(__string__,1,2)))
		__attribute__((__bounded__(__minbytes__,3,MD5_DIGEST_LENGTH)));

#endif
