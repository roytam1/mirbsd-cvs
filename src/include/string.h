/**	$MirOS: src/include/string.h,v 1.15 2015/02/09 21:50:44 tg Exp $ */
/*	$OpenBSD: string.h,v 1.15 2005/03/30 03:04:16 deraadt Exp $	*/
/*	$NetBSD: string.h,v 1.6 1994/10/26 00:56:30 cgd Exp $	*/

/*-
 * Copyright © 2013, 2014, 2015
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)string.h	5.10 (Berkeley) 3/9/91
 */

#ifndef _STRING_H_
#define	_STRING_H_

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
#include <sys/types.h>		/* for mode_t */
#else
#include <sys/cdefs.h>
#include <machine/ansi.h>
#endif

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__	size_t;
#endif

/* C11 optional */
#if !defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__)
#ifndef rsize_t
#define rsize_t		rsize_t
typedef size_t		rsize_t;
#endif
#endif /* __STDC_WANT_LIB_EXT1__ */

#ifndef NULL
#ifdef __GNUG__
#define	NULL		__null
#elif defined(lint) || defined(__cplusplus)
#define	NULL		0UL
#else
#define	NULL		((void *)((__PTRDIFF_TYPE__)0UL))
#endif
#endif

__BEGIN_DECLS
void	*memchr(const void *, int, size_t);
int	 memcmp(const void *, const void *, size_t);
void	*memcpy(void *, const void *, size_t)
		__attribute__((__bounded__(__buffer__, 1, 3)))
		__attribute__((__bounded__(__buffer__, 2, 3)));
void	*memmove(void *, const void *, size_t)
		__attribute__((__bounded__(__buffer__, 1, 3)))
		__attribute__((__bounded__(__buffer__, 2, 3)));
void	*memset(void *, int, size_t)
		__attribute__((__bounded__(__buffer__, 1, 3)));
char	*strcat(char *, const char *);
char	*strchr(const char *, int);
int	 strcmp(const char *, const char *);
int	 strcoll(const char *, const char *);
char	*strcpy(char *, const char *);
size_t	 strcspn(const char *, const char *);
char	*strerror(int);
int	 strerror_r(int, char *, size_t)
		__attribute__((__bounded__(__string__, 2, 3)));
size_t	 strlen(const char *);
char	*strncat(char *, const char *, size_t)
		__attribute__((__bounded__(__string__, 1, 3)));
int	 strncmp(const char *, const char *, size_t);
char	*strncpy(char *, const char *, size_t)
		__attribute__((__bounded__(__string__, 1, 3)));
char	*strpbrk(const char *, const char *);
char	*strrchr(const char *, int);
size_t	 strspn(const char *, const char *);
char	*strstr(const char *, const char *);
char	*strtok(char *, const char *);
char	*strtok_r(char *, const char *, char **);
size_t	 strxfrm(char *, const char *, size_t)
		__attribute__((__bounded__(__string__, 1, 3)));

/* Nonstandard routines */
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
int	 bcmp(const void *, const void *, size_t);
void	 bcopy(const void *, void *, size_t)
		__attribute__((__bounded__(__buffer__, 1, 3)))
		__attribute__((__bounded__(__buffer__, 2, 3)));
void	 bzero(void *, size_t)
		__attribute__((__bounded__(__buffer__, 1, 2)));
#if __OPENBSD_VISIBLE
void explicit_bzero(void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 2)));
#endif
int	 ffs(int);
char	*index(const char *, int);
void	*memccpy(void *, const void *, int, size_t)
		__attribute__((__bounded__(__buffer__, 1, 4)));
char	*rindex(const char *, int);
int	 strcasecmp(const char *, const char *);
char	*strdup(const char *);
char	*strcasestr(const char *, const char *);
size_t	 strlcat(char *, const char *, size_t)
		__attribute__((__bounded__(__string__, 1, 3)));
size_t	 strlcpy(char *, const char *, size_t)
		__attribute__((__bounded__(__string__, 1, 3)));
void	 strmode(mode_t, char *);
int	 strncasecmp(const char *, const char *, size_t);
#if __OPENBSD_VISIBLE
char	*strndup(const char *, size_t);
size_t	 strnlen(const char *, size_t);
#endif
char	*strsep(char **, const char *);
char	*strsignal(int);
#endif
#if __OPENBSD_VISIBLE
int timingsafe_bcmp(const void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
int timingsafe_memcmp(const void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
#endif
__END_DECLS

#if defined(_GNU_SOURCE) && !defined(__STRICT_ANSI__)
__BEGIN_DECLS
char *stpcpy(char *, const char *);
char *stpncpy(char *, const char *, size_t)
    __attribute__((__bounded__(__string__, 1, 3)));
void *mempcpy(void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
__END_DECLS
#endif

#endif /* _STRING_H_ */
