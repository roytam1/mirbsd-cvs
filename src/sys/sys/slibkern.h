/**	$MirOS: src/sys/sys/slibkern.h,v 1.4 2013/10/31 20:07:00 tg Exp $ */
/*	$OpenBSD: libkern.h,v 1.22 2004/08/07 00:38:32 deraadt Exp $	*/
/*	$NetBSD: libkern.h,v 1.7 1996/03/14 18:52:08 christos Exp $	*/

/*-
 * Copyright © 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)libkern.h	8.1 (Berkeley) 6/10/93
 */

#ifndef __LIBKERN_H__
#define __LIBKERN_H__

#if defined(_KERNEL) || defined(_STANDALONE)
#include <libckern.h>
#else
#include <syskern/libckern.h>
#endif

#ifdef NDEBUG						/* tradition! */
#define	assert(e)	((void)0)
#else
#ifdef __STDC__
#define	assert(e)	((e) ? (void)0 :				    \
			    __assert("", __FILE__, __LINE__, #e))
#else
#define	assert(e)	((e) ? (void)0 :				    \
			    __assert("", __FILE__, __LINE__, "e"))
#endif
#endif

#ifndef DIAGNOSTIC
#define	KASSERT(e)	((void)0)
#else
#ifdef __STDC__
#define	KASSERT(e)	((e) ? (void)0 :				    \
			    __assert("diagnostic ", __FILE__, __LINE__, #e))
#else
#define	KASSERT(e)	((e) ? (void)0 :				    \
			    __assert("diagnostic ", __FILE__, __LINE__, "e"))
#endif
#endif

#ifndef DEBUG
#define	KDASSERT(e)	((void)0)
#else
#ifdef __STDC__
#define	KDASSERT(e)	((e) ? (void)0 :				    \
			    __assert("debugging ", __FILE__, __LINE__, #e))
#else
#define	KDASSERT(e)	((e) ? (void)0 :				    \
			    __assert("debugging ", __FILE__, __LINE__, "e"))
#endif
#endif

/* Prototypes for non-quad routines. */
void	 __assert(const char *, const char *, int, const char *)
	    __attribute__((__noreturn__));
int	 locc(int, char *, u_int);
int	 scanc(u_int, const u_char *, const u_char [], int);
int	 skpc(int, size_t, u_char *);
int	 getsn(char *, int);

extern u_int8_t const __bcd2bin[], __bin2bcd[];
#define	bcd2bin(b)	(__bcd2bin[(b)&0xff])
#define	bin2bcd(b)	(__bin2bcd[(b)&0xff])

#define memcpy(d,s,n)	memmove((d), (s), (n))
#define bcopy(s,d,n)	(void)memmove((d), (s), (n))

#endif /* __LIBKERN_H__ */
