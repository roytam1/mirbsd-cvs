/* $MirOS: contrib/code/mirmake/dist/contrib/mirmake.h,v 1.3 2005/02/28 20:09:23 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 *-
 * Add here: macros not defined on every operating system, for easier
 * patching of ported apps.
 * Suggest to use with CPPFLAGS+= -imacros "/path/to/mirmake.h" (safe
 * or conservative) or CPPFLAGS+= -include "/path/to/mirmake.h"
 */

#ifndef _MIRMAKE_H
#define _MIRMAKE_H

#ifdef __INTERIX
/* stock Interix/SFU needs this, MirInterix not */
#define _ALL_SOURCE
#endif

#include <sys/types.h>

#ifndef __IDSTRING
#ifdef lint
#define	__IDSTRING(prefix, string)				\
	static const char __ ## prefix [] = (string)
#elif defined(__ELF__) && defined(__GNUC__)
#define	__IDSTRING(prefix, string)				\
	__asm__(".section .comment"				\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define	__IDSTRING(prefix, string)				\
	static const char __ ## prefix []			\
	    __attribute__((__unused__)) = (string)
#endif
#endif
#ifndef __KERNEL_RCSID
#ifdef lint
#define	__KERNEL_RCSID(n,x)	__IDSTRING(rcsid_ ## n,x)
#else
#define	__KERNEL_RCSID(n,x)	/* nothing */
#endif
#endif
#ifndef __RCSID
#define	__RCSID(x)		__IDSTRING(rcsid,x)
#endif
#ifndef __SCCSID
#define	__SCCSID(x)		__IDSTRING(sccsid,x)
#endif

#ifndef	SA_LEN
#define	SA_LEN(x)	(((x)->sa_family == AF_INET6) ? \
			    sizeof(struct sockaddr_in6) : \
			    (((x)->sa_family == AF_INET) ? \
				sizeof(struct sockaddr_in) : \
				sizeof(struct sockaddr)))
#endif

#ifndef __BEGIN_DECLS
#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif /* ndef __BEGIN_DECLS */

#ifndef _NO_DECLS
__BEGIN_DECLS
size_t	 strlcat(char *, const char *, size_t);
size_t	 strlcpy(char *, const char *, size_t);
__END_DECLS
#endif

#endif /* ndef _MIRMAKE_H */
