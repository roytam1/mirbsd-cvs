/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
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

/* extern __inline is a GNU C extension */
#ifdef __GNUC__
#define	__CTYPE_INLINE	extern __inline
#else
#define	__CTYPE_INLINE	static __inline
#endif

#define __CTYPE_IMPL(t)							     \
	__CTYPE_INLINE int is ## t (int c)				     \
	{								     \
		if ((c < 0) || (c > 255))				     \
			return (0);					     \
		return ((__C_attribute_table_pg[c] & (_ctp_ ## t & 0xFF)) && \
		    !(__C_attribute_table_pg[c] & (_ctp_ ## t >> 8)));	     \
	}

__CTYPE_IMPL(alnum)
__CTYPE_IMPL(alpha)
__CTYPE_IMPL(cntrl)
__CTYPE_IMPL(digit)
__CTYPE_IMPL(graph)
__CTYPE_IMPL(lower)
__CTYPE_IMPL(print)
__CTYPE_IMPL(punct)
__CTYPE_IMPL(space)
__CTYPE_IMPL(upper)
__CTYPE_IMPL(xdigit)

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
__CTYPE_INLINE int isascii(int c)
{
	return ((unsigned int)c <= 0177);
}

__CTYPE_IMPL(blank)

__CTYPE_INLINE int toascii(int c)
{
	return (c & 0177);
}

/* SUSv3 says these are always macros */
#define _tolower(c)	((c) - 'A' + 'a')
#define _toupper(c)	((c) - 'a' + 'A')

#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#undef __CTYPE_IMPL
#undef __CTYPE_INLINE

#endif /* !_ANSI_LIBRARY && !lint */

__END_DECLS

#endif /* !_CTYPE_H_ */
