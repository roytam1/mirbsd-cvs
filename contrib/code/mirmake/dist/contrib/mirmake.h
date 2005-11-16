/* $MirOS: contrib/code/mirmake/dist/contrib/mirmake.h,v 1.16 2005/11/10 12:58:08 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Based upon some code
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 * The acknowledgement needs not to be reprinted if this software was
 * only used in compiling the redistributed work.
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
 * patching of ported apps. Same for definitions of libmirmake, these
 * are only declared if _MIRMAKE_DEFNS is defined first.
 * Suggest to use with CPPFLAGS+= -include "/path/to/mirmake.h" - but
 * take care of CPP uses with assembly source.
 */

#if !defined(_MIRMAKE_H) && !defined(_ASM_SOURCE)
#define _MIRMAKE_H

#ifdef __INTERIX
/* stock Interix/SFU needs this, MirInterix not */
#define _ALL_SOURCE
#endif

#include <sys/cdefs.h>
#include <sys/types.h>

/* Undefining */

#ifdef __INTERIX
#undef __dead
#undef __pure
#endif

/* Redefining */

#ifndef __BEGIN_DECLS
#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif /* ndef __BEGIN_DECLS */

#ifndef __GNUC_PREREQ__
#ifdef __GNUC__
#define __GNUC_PREREQ__(ma, mi) \
	((__GNUC__ > (ma)) || (__GNUC__ == (ma) && __GNUC_MINOR__ >= (mi)))
#else
#define __GNUC_PREREQ__(ma, mi) 0
#endif
#endif

#define	__P(protos)	protos
#define	__CONCAT(x,y)	x ## y
#define	__STRING(x)	#x

#define	__const		const
#define	__signed	signed
#define	__volatile	volatile
#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#elif !defined(__GNUC__) && !defined(lint)
#define	__inline			/* delete GCC keyword */
#endif

#ifndef __dead
#if !__GNUC_PREREQ__(2, 5)
#define	__attribute__(x)	/* delete __attribute__ if no or old gcc */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define	__dead		__volatile
#define	__pure		__const
#endif
#elif __GNUC_PREREQ__(3, 4) || !defined(__STRICT_ANSI__)
#define __dead		__attribute__((__noreturn__))
#define __pure		__attribute__((__const__))
#else
#define	__dead
#define	__pure
#endif
#endif

#ifndef __weak_extern
#ifdef __ELF__
#define __weak_extern(sym)	__asm__(".weak " #sym);
#else
#define __weak_extern(sym)	/* XXX FIXME */
#endif
#endif

#ifndef __packed
#if __GNUC__ >= 3
#define	__packed		__attribute__((packed))
#elif __GNUC_PREREQ__(2, 7)
#define	__packed		__attribute__((__packed__))
#elif defined(lint)
#define	__packed
#endif
#endif

#if !__GNUC_PREREQ__(2, 8) && !defined(__extension__)
#define	__extension__
#endif

#ifndef __IDSTRING
#ifdef lint
#define	__IDSTRING(prefix, string)				\
	static const char __LINTED__ ## prefix [] = (string)
#elif defined(__ELF__) && defined(__GNUC__)
#define	__IDSTRING(prefix, string)				\
	__asm__(".section .comment"				\
	"\n	.ascii	\"" #prefix ": \""			\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define	__IDSTRING(prefix, string)				\
	static const char __ ## prefix []			\
	    __attribute__((used)) = (string)
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

/* Additions */

#ifndef	SA_LEN
#ifdef __INTERIX
/* any system without AF_INET6 */
#define	SA_LEN(x)	(((x)->sa_family == AF_INET) ? \
			    sizeof(struct sockaddr_in) : \
			    sizeof(struct sockaddr))
#else
#define	SA_LEN(x)	(((x)->sa_family == AF_INET6) ? \
			    sizeof(struct sockaddr_in6) : \
			    (((x)->sa_family == AF_INET) ? \
				sizeof(struct sockaddr_in) : \
				sizeof(struct sockaddr)))
#endif
#endif

#ifdef _MIRMAKE_DEFNS
__BEGIN_DECLS

#if !defined(BSD) && !defined(__APPLE__)
size_t strlcat(char *, const char *, size_t);
size_t strlcpy(char *, const char *, size_t);
#endif

#if defined(__INTERIX)
char	*mkdtemp(char *);
int	 mkstemps(char *, int);
/* LONGLONG */
long long
	 strtoll(const char *, char **, int);
quad_t	 strtoq(const char *, char **, int);
int	 asprintf(char **, const char *, ...)
		__attribute__((__format__ (printf, 2, 3)))
		__attribute__((__nonnull__ (2)));
int	 vasprintf(char **, const char *, __builtin_va_list)
		__attribute__((__format__ (printf, 2, 0)))
		__attribute__((__nonnull__ (2)));
#endif

__END_DECLS
#endif

#endif /* ndef _MIRMAKE_H && ndef _ASM_SOURCE */
