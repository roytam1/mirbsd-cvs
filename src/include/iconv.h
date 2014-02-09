/* $MirOS: src/include/iconv.h,v 1.5 2006/12/11 23:54:56 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * Expose standardised iconv(3) interface, implementation-independent
 */

#ifndef _ICONV_H_
#define _ICONV_H_

#include <sys/cdefs.h>
#include <machine/ansi.h>

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__	size_t;
#endif

#ifndef _ICONV_HAVE_ICONV_T
typedef void *iconv_t;
#endif

__BEGIN_DECLS
iconv_t iconv_open(const char *, const char *);
size_t iconv(iconv_t, char **, size_t *, char **, size_t *);
int iconv_close(iconv_t);
__END_DECLS

#ifdef _ALL_SOURCE
/* non-portable NetBSD(R) interface */
__BEGIN_DECLS
int __iconv_get_list(char ***, size_t *);
void __iconv_free_list(char **, size_t);
size_t __iconv(iconv_t, const char **, size_t *, char **, size_t *,
    u_int32_t, size_t *);
__END_DECLS
#endif /* _ALL_SOURCE */

#endif
