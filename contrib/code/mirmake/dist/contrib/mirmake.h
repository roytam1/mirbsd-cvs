/**	$MirOS$ */

/*-
 * Copyright (c) 2004
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
 */

#ifndef _MIRMAKE_H
#define _MIRMAKE_H

#include <sys/types.h>

#ifndef __RCSID
#define __RCSID(x)	static const char __rcsid[] = (x)
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
