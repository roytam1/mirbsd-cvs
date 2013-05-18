/* $MirOS: src/share/misc/licence.template,v 1.8 2006/06/16 23:03:39 tg Rel $ */

/*-
 * Copyright (c) 2005
 *	Thorsten Glaser <tg@mirbsd.de>
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
 * This acknowledgement does not need to be reprinted if this work is
 * linked into a bigger work whose licence does not allow such clause
 * and the author of this work is given due credit in the bigger work
 * or its documentation. Specifically, re-using this code in any work
 * covered by the GNU General Public License version 1 or Library Ge-
 * neral Public License (any version) is permitted.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
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

#ifndef __P
#define	__P(protos)	protos
#endif
#ifndef __CONCAT
#define	__CONCAT(x,y)	x ## y
#endif
#ifndef __STRING
#define	__STRING(x)	#x
#endif

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

#ifdef __APPLE__
#define uint8_t u_int8_t
#define uint16_t u_int16_t
#define uint32_t u_int32_t
#define uint64_t u_int64_t
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
