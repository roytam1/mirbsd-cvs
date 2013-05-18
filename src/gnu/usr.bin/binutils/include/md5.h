/* $MirOS: src/gnu/usr.bin/binutils/include/md5.h,v 1.2 2005/03/13 16:07:00 tg Exp $ */

#ifndef _MD5_H

#ifdef __OpenBSD__
/* include md5 functions from libc */
#include "/usr/include/md5.h"
#else
#include_next "md5.h"
#endif

#ifdef _MD5_H_
#define _MD5_H

#define	md5_ctx				MD5Context
#define	md5_init_ctx			MD5Init
#define	md5_process_bytes(buf,len,ctx)	\
	    MD5Update((ctx), (const unsigned char *)(buf), (len))
#define	md5_finish_ctx(ctx,buf)		\
	    MD5Final((unsigned char *)(buf), (ctx))
#endif

#endif
