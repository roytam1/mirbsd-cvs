/* $MirOS: src/usr.sbin/httpd/src/include/ap_md5.h,v 1.3 2005/04/17 04:38:32 tg Exp $ */

#ifndef	APACHE_MD5_H

/* include md5 functions from libc */
#include "/usr/include/md5.h"
#ifdef	_MD5_H_
#define	APACHE_MD5_H

#define	MD5_DIGESTSIZE			MD5_DIGEST_LENGTH
#define	UINT4				u_int32_t
#define	AP_MD5_CTX			MD5_CTX
#define	AP_MD5PW_ID			"$apr1$"
#define	AP_MD5PW_IDLEN			6
#define	ap_MD5Init			MD5Init
#define	ap_MD5Update(ctx,buf,len)	\
	    MD5Update((ctx), (buf), (size_t)(len))
#define	ap_MD5Final			MD5Final

__BEGIN_DECLS
void ap_to64(char *, unsigned long, int);
void ap_MD5Encode(const unsigned char *, const unsigned char *,
    char *, size_t);
__END_DECLS

#endif
#endif
