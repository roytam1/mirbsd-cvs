/**	$MirOS: src/sys/arch/i386/include/ansi.h,v 1.3 2005/03/26 10:56:10 tg Exp $ */
/*	$OpenBSD: ansi.h,v 1.9 2004/01/03 14:08:52 espie Exp $	*/
/*	$NetBSD: ansi.h,v 1.7 1996/11/15 22:38:50 jtc Exp $	*/

/*-
 * Copyright (c) 1990, 1993
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
 *	@(#)ansi.h	8.2 (Berkeley) 1/4/94
 */

#ifndef	_ANSI_H_
#define	_ANSI_H_

/*
 * Types which are fundamental to the implementation and may appear in
 * more than one standard header are defined here.  Standard headers
 * then use:
 *	#ifdef	_BSD_SIZE_T_
 *	typedef	_BSD_SIZE_T_ size_t;
 *	#undef	_BSD_SIZE_T_
 *	#endif
 */
#define	_BSD_CLOCK_T_	unsigned long		/* clock() */
#define	_BSD_PTRDIFF_T_	int			/* ptr1 - ptr2 */
#define	_BSD_SIZE_T_	unsigned int		/* sizeof() */
#define	_BSD_SSIZE_T_	int			/* byte count or error */
#ifdef __BIT_TYPES_DEFINED__
#define	_BSD_TIME_T_	int64_t			/* time() */
#else
/* LONGLONG */
#define	_BSD_TIME_T_	long long		/* time() */
#endif
#define	_BSD_TIME_T_IS_64_BIT
#if defined(__GNUC__) && __GNUC__ >= 3
#define _BSD_VA_LIST_	__builtin_va_list
#else
#define	_BSD_VA_LIST_	char *			/* va_list */
#endif
#define _BSD_CLOCKID_T_	int
#define _BSD_TIMER_T_	int

/*
 * wchar_t is declared to be an "unsigned short" for size reasons on MirOS,
 * so we can only support the BMP, but this is okay for us.  We also only
 * support UTF-8 and ISO-8859-1/transparent encodings externally, and UCS-2
 * is only being used internally, in machine endianness.
 * wint_t must be an int or unsigned int because of integer promotion rules.
 */
#define	_BSD_WCHAR_T_	unsigned short		/* wchar_t */
#define _BSD_WINT_T_	int			/* wint_t */

/*
 * We describe off_t here so its declaration can be visible to
 * stdio without pulling in all of <sys/types.h>, thus appeasing ANSI.
 */
#ifdef __BIT_TYPES_DEFINED__
#define _BSD_OFF_T_	int64_t			/* file offset */
#else
/* LONGLONG */
#define _BSD_OFF_T_	long long		/* file offset */
#endif

#endif	/* _ANSI_H_ */
