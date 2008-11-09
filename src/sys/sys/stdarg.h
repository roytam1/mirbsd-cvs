/* $MirOS: src/sys/sys/stdarg.h,v 1.3 2007/10/01 21:05:40 tg Exp $ */

/*-
 * Copyright (c) 2007, 2008
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
 */

#ifndef _STDARG_H
#define _STDARG_H

/* ragge's pcc and gcc3+ do stdargs in a machine-independent way */
#if (defined(__PCC__) && ((__PCC__ > 0) || (__PCC_MINOR__ > 9) || \
     ((__PCC_MINOR__ == 9) && (__PCC_MINORMINOR__ > 8)))) || \
    (defined(__GNUC__) && (__GNUC__ >= 3)) || \
    (defined(__llvm__) && defined(__clang__))

#ifdef __PCC__
typedef char *va_list;
#else /* !__PCC__ */
#include <machine/ansi.h>

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif

typedef __gnuc_va_list va_list;
#endif /* !__PCC__ */

#if defined(__llvm__) && defined(__clang__)
#define va_start(ap,list)	__builtin_va_start((ap), (list))
#else
#define va_start(ap,list)	__builtin_stdarg_start((ap), (list))
#endif
/* note: “type” must be promoted, i.e. “short” is not valid, use “int” */
#define va_arg(ap,type)		__builtin_va_arg((ap), type)
#define va_end(ap)		__builtin_va_end(ap)

#if !defined(_ANSI_SOURCE) && \
    (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) || \
     defined(_ISOC99_SOURCE) || (__STDC_VERSION__ - 0) >= 199901L)
#define va_copy(dst,src)	__builtin_va_copy((dst), (src))
#endif

#else /* ! pcc > 0.9.8 || gcc >= 3 */
/* try to cover up for type and stack alignment, etc. */
#include <machine/stdarg.h>
#endif /* ! pcc > 0.9.8 || gcc >= 3 */

#endif /* !_STDARG_H */
