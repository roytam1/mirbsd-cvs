/* $MirOS: src/sys/sys/stddef.h,v 1.4 2015/02/09 21:50:45 tg Exp $ */
/* $OpenBSD: src/include/stddef.h,v 1.8 2005/05/11 18:44:12 espie Exp $ */
/* $NetBSD: stddef.h,v 1.4 1994/10/26 00:56:26 cgd Exp $ */

/*-
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
 *	@(#)stddef.h	5.5 (Berkeley) 4/3/91
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <machine/ansi.h>

#if !defined(_GCC_PTRDIFF_T)
#define	_GCC_PTRDIFF_T
typedef	__PTRDIFF_TYPE__	ptrdiff_t;
#endif

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__		size_t;
#endif

/* C11 optional */
#if !defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__)
#ifndef rsize_t
#define rsize_t			rsize_t
typedef size_t			rsize_t;
#endif
#endif /* __STDC_WANT_LIB_EXT1__ */

#if !defined(_GCC_WCHAR_T) && !defined(__cplusplus)
#define	_GCC_WCHAR_T
typedef	__WCHAR_TYPE__		wchar_t;
#endif

#if !defined(_GCC_WINT_T)
#define	_GCC_WINT_T
typedef	__WINT_TYPE__		wint_t;
#endif

#ifndef NULL
#ifdef __GNUG__
#define	NULL			__null
#elif defined(lint) || defined(__cplusplus)
#define	NULL			0UL
#else
#define	NULL			((void *)((__PTRDIFF_TYPE__)0UL))
#endif
#endif

#ifndef offsetof
#if (defined(__GNUC__) && (__GNUC__ > 3)) || defined(__NWCC__)
#define offsetof(s, e)		__builtin_offsetof(s, e)
#elif defined(__cplusplus)
#define offsetof(s, e)						\
		(__offsetof__ (reinterpret_cast <size_t>	\
		    (&reinterpret_cast <const volatile char &>	\
		    (static_cast<s *> (0)->e))))
#else
#define offsetof(s, e)		((size_t)&((s *)0)->e)
#endif
#endif

#endif /* _STDDEF_H_ */
