/* $MirOS: contrib/code/mirmake/dist/contrib/mirmake.h,v 1.48 2011/01/24 21:26:19 tg Exp $ */

/*-
 * Copyright (c) 2005, 2006, 2008, 2009, 2011, 2013
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * Partially based upon some code
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
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
 * Add here: macros not defined on every operating system, for easier
 * patching of ported apps. Same for definitions of libmirmake, these
 * are only declared if _MIRMAKE_DEFNS is defined first.
 * Suggest to use with CPPFLAGS+= -include "/path/to/mirmake.h" - but
 * take care of CPP uses with assembly source.
 */

#if !defined(_MIRMAKE_H) && !defined(_ASM_SOURCE)
#define _MIRMAKE_H

#if defined(__INTERIX)
/* stock Interix/SFU needs this, MirInterix not */
#undef _ALL_SOURCE
#define _ALL_SOURCE
#elif defined(__APPLE__)
/* some OSX versions started to require this to fight POSIX header idiocy */
#undef _DARWIN_C_SOURCE
#define _DARWIN_C_SOURCE
#elif defined(__GLIBC__)
/* similarily, allow all extensions */
#undef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/param.h>
#if defined(__GLIBC__)
#include <endian.h>
#elif !defined(__APPLE__)
#include <sys/endian.h>
#endif

/* Undefining */

#if defined(__INTERIX) || defined(__APPLE__)
/* neither Interix nor Darwin get __dead and __pure right… */
#undef __dead
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
#if (defined(__cplusplus) || defined(__PCC__)) && !defined(__inline)
#define	__inline	inline		/* convert to C++/C99 keyword */
#elif !defined(__GNUC__) && !defined(lint) && !defined(__inline)
#define	__inline			/* delete GCC keyword */
#endif

#ifndef __dead
#undef __pure
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
#define	__packed		__attribute__((__packed__))
#elif __GNUC_PREREQ__(2, 7)
#define	__packed		__attribute__((__packed__))
#elif defined(lint)
#define	__packed
#endif
#endif

#if !__GNUC_PREREQ__(2, 8) && !defined(__extension__)
#define	__extension__
#endif

#ifdef lint
#ifndef __aligned
#define __aligned(x)
#endif
#ifndef __func__
#define __func__		"__func__"
#endif
#ifndef __restrict__
#define __restrict__
#endif
#ifndef __unused
#define __unused
#endif
#elif defined(__PCC__)
#ifndef __aligned
#define __aligned(x)		_Pragma("aligned " #x)
#endif
#ifndef __restrict__
#define __restrict__		restrict
#endif
#ifndef __unused
#define __unused
#endif
#else
#ifndef __aligned
#define __aligned(x)		__attribute__((__aligned__(x)))
#endif
#ifndef __unused
#define __unused		__attribute__((__unused__))
#endif
#endif

#undef __IDSTRING
#undef __IDSTRING_CONCAT
#undef __IDSTRING_EXPAND
#undef __COPYRIGHT
#undef __KERNEL_RCSID
#undef __RCSID
#undef __SCCSID
#undef __FBSDID
#if defined(__ELF__) && defined(__GNUC__)
#define __IDSTRING(prefix, string)				\
	__asm__(".section .comment"				\
	"\n	.ascii	\"@(\"\"#)" #prefix ": \""		\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define __IDSTRING_CONCAT(l,p)		__LINTED__ ## l ## _ ## p
#define __IDSTRING_EXPAND(l,p)		__IDSTRING_CONCAT(l,p)
#define __IDSTRING(prefix, string)				\
	static const char __IDSTRING_EXPAND(__LINE__,prefix) []	\
	    __attribute__((__used__)) = "@(""#)" #prefix ": " string
#endif
#define __COPYRIGHT(x)		__IDSTRING(copyright,x)
#ifdef lint
#define	__KERNEL_RCSID(n,x)	__IDSTRING(rcsid_ ## n,x)
#else
#define	__KERNEL_RCSID(n,x)	/* nothing */
#endif
#define	__RCSID(x)		__IDSTRING(rcsid,x)
#define	__SCCSID(x)		__IDSTRING(sccsid,x)
#define	__FBSDID(x)		__IDSTRING(fbsdid,x)

#ifndef _DIAGASSERT
#define _DIAGASSERT(x)		/* nothing */
#endif

/* Additions */

#ifndef	SA_LEN
#ifdef __INTERIX
/* any system without AF_INET6 */
#define	SA_LEN(x)	(((x)->sa_family == AF_INET) ? \
			    sizeof(struct sockaddr_in) : \
			    sizeof(struct sockaddr))
#elif defined(__APPLE__)
#define	SA_LEN(x)	(((struct sockaddr *)(x))->sa_len)
#elif !defined(BSD) /* from <sys/param.h> */
#define	SA_LEN(x)	(((x)->sa_family == AF_INET6) ? \
			    sizeof(struct sockaddr_in6) : \
			    (((x)->sa_family == AF_INET) ? \
				sizeof(struct sockaddr_in) : \
				sizeof(struct sockaddr)))
#endif
#endif

#if defined(__APPLE__)
#define uint8_t u_int8_t
#define uint16_t u_int16_t
#define uint32_t u_int32_t
#define uint64_t u_int64_t
#include <libkern/OSByteOrder.h>
#elif defined(__GLIBC__)
#include <byteswap.h>
#include <stdint.h>
#elif defined(__INTERIX)
#define uint64_t u_int64_t
#endif

/* brain-dead Apple stuff */
#ifdef OSSwapLittleToHostInt16
#define letoh16(x)	OSSwapLittleToHostInt16(x)
#define letoh32(x)	OSSwapLittleToHostInt32(x)
#define letoh64(x)	OSSwapLittleToHostInt64(x)
#define betoh16(x)	OSSwapBigToHostInt16(x)
#define betoh32(x)	OSSwapBigToHostInt32(x)
#define betoh64(x)	OSSwapBigToHostInt64(x)
#define htole16(x)	OSSwapHostToLittleInt16(x)
#define htole32(x)	OSSwapHostToLittleInt32(x)
#define htole64(x)	OSSwapHostToLittleInt64(x)
#define htobe16(x)	OSSwapHostToBigInt16(x)
#define htobe32(x)	OSSwapHostToBigInt32(x)
#define htobe64(x)	OSSwapHostToBigInt64(x)
#endif

/* GNU libc */
#if !defined(htobe16) && defined(__bswap_16) && defined(_ENDIAN_H)
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define letoh16(x)	(x)
#define letoh32(x)	(x)
#define letoh64(x)	(x)
#define betoh16(x)	__bswap_16(x)
#define betoh32(x)	__bswap_32(x)
#define betoh64(x)	__bswap_64(x)
#define htole16(x)	(x)
#define htole32(x)	(x)
#define htole64(x)	(x)
#define htobe16(x)	__bswap_16(x)
#define htobe32(x)	__bswap_32(x)
#define htobe64(x)	__bswap_64(x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define letoh16(x)	__bswap_16(x)
#define letoh32(x)	__bswap_32(x)
#define letoh64(x)	__bswap_64(x)
#define betoh16(x)	(x)
#define betoh32(x)	(x)
#define betoh64(x)	(x)
#define htole16(x)	__bswap_16(x)
#define htole32(x)	__bswap_32(x)
#define htole64(x)	__bswap_64(x)
#define htobe16(x)	(x)
#define htobe32(x)	(x)
#define htobe64(x)	(x)
#endif
#endif

/* apparently, MidnightBSD needs these */
#if defined(be16toh) && !defined(betoh16)
#define betoh16(x)	be16toh(x)
#define betoh32(x)	be32toh(x)
#define betoh64(x)	be64toh(x)
#define letoh16(x)	le16toh(x)
#define letoh32(x)	le32toh(x)
#define letoh64(x)	le64toh(x)
#endif

#ifdef _MIRMAKE_DEFNS
__BEGIN_DECLS

#if !defined(BSD) && !defined(__APPLE__)
#include <stdio.h>	/* for FILE - C sucks here */
#endif

#if !defined(BSD) && !defined(__APPLE__)
char *fgetln(FILE *, size_t *);
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
		__attribute__((__format__(__printf__, 2, 3)))
		__attribute__((__nonnull__(2)));
int	 vasprintf(char **, const char *, __builtin_va_list)
		__attribute__((__format__(__printf__, 2, 0)))
		__attribute__((__nonnull__(2)));
#endif

#if !defined(BSD) && !defined(__INTERIX)
u_int32_t arc4random(void);
void arc4random_stir(void);
void arc4random_addrandom(unsigned char *, int)
    __attribute__((__bounded__(__string__, 1, 2)));
#endif

__END_DECLS
#endif

#endif
