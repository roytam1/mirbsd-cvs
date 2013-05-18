/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

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
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include <sys/cdefs.h>

/* Idea from Bruno Haible's libutf8 */
#define _ctp_alnum	0x000C
#define _ctp_alpha	0x0004
#define _ctp_blank	0x0040
#define _ctp_cntrl	0x0080
#define _ctp_digit	0x0408
#define _ctp_graph	0x1020
#define _ctp_lower	0x0002
#define _ctp_print	0x0020
#define _ctp_punct	0x1C20
#define _ctp_space	0x0010
#define _ctp_upper	0x0001
#define _ctp_xdigit	0x0008

__BEGIN_DECLS
extern const unsigned char __C_attribute_table_pg[256];

#if defined(__GNUC__) || defined(_ANSI_LIBRARY) || defined(lint)
int	isalnum(int);
int	isalpha(int);
int	iscntrl(int);
int	isdigit(int);
int	isgraph(int);
int	islower(int);
int	isprint(int);
int	ispunct(int);
int	isspace(int);
int	isupper(int);
int	isxdigit(int);
int	tolower(int);
int	toupper(int);

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
int	isascii(int);
int	isblank(int);
int	toascii(int);
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#endif /* __GNUC__ || _ANSI_LIBRARY || lint */

#if !defined(_ANSI_LIBRARY) && !defined(lint)

/*
 * Kludge for the macro version:
 * ANSI requires that only the 7-bit ASCII range is letters.
 * With ISO-8859-1, 0x80..0x9F are cntrl, and 0xA0..0xFF are
 * print, but with UTF-8, they are neither cntrl, nor print.
 * So I decided to have a pure ISO_646.irv:1991 macro imple-
 * mentation, and the function implementation return cntrl /
 * print if MIR18N_C_CSET == 2, 0 otherwise, for 8bit chars.
 */

#ifdef __GNUC__
#define __CTYPE_IMPL(c,t) __extension__({				\
	unsigned __CTYPE_Ic = (c);					\
	(__CTYPE_Ic > 127) ? 0 :					\
	 ((__C_attribute_table_pg[__CTYPE_Ic] & (_ctp_ ## t & 0xFF)) &&	\
	 !(__C_attribute_table_pg[__CTYPE_Ic] & (_ctp_ ## t >> 8)));	\
})
#else
#define __CTYPE_IMPL(c,t)						\
	(((((int)(c)) < 0) || (((int)(c)) > 127)) ? 0 :			\
	 ((__C_attribute_table_pg[((int)(c))] & (_ctp_ ## t & 0xFF)) &&	\
	 !(__C_attribute_table_pg[((int)(c))] & (_ctp_ ## t >> 8))))
#endif

#define isalnum(c)	__CTYPE_IMPL((c),alnum)
#define isalpha(c)	__CTYPE_IMPL((c),alpha)
#define iscntrl(c)	__CTYPE_IMPL((c),cntrl)
#define isdigit(c)	__CTYPE_IMPL((c),digit)
#define isgraph(c)	__CTYPE_IMPL((c),graph)
#define islower(c)	__CTYPE_IMPL((c),lower)
#define isprint(c)	__CTYPE_IMPL((c),print)
#define ispunct(c)	__CTYPE_IMPL((c),punct)
#define isspace(c)	__CTYPE_IMPL((c),space)
#define isupper(c)	__CTYPE_IMPL((c),upper)
#define isxdigit(c)	__CTYPE_IMPL((c),xdigit)

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
#define isascii(c)	((unsigned int)(c) <= 0177)
#define isblank(c)	__CTYPE_IMPL((c),blank)
#define toascii(c)	((c) & 0177)

/* SUSv3 says these are always macros */
#define _tolower(c)	(((c) >= 'A') && ((c) <= 'Z') ? (c) - 'A' + 'a' : (c))
#define _toupper(c)	(((c) >= 'a') && ((c) <= 'z') ? (c) - 'a' + 'A' : (c))

#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#endif /* !_ANSI_LIBRARY && !lint */

__END_DECLS

#endif /* !_CTYPE_H_ */
