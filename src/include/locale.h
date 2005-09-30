/*	$MirOS: src/include/locale.h,v 1.3 2005/09/22 19:53:04 tg Exp $	*/
/*	$OpenBSD: locale.h,v 1.6 2003/06/02 19:34:12 millert Exp $	*/
/*	$NetBSD: locale.h,v 1.6 1994/10/26 00:56:02 cgd Exp $	*/

/*
 * Copyright (c) 1991 The Regents of the University of California.
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
 *	@(#)locale.h	5.2 (Berkeley) 2/24/91
 */

#ifndef _LOCALE_H_
#define _LOCALE_H_

#include <sys/cdefs.h>

struct lconv {
	const char	*decimal_point;
	const char	*thousands_sep;
	const char	*grouping;
	const char	*int_curr_symbol;
	const char	*currency_symbol;
	const char	*mon_decimal_point;
	const char	*mon_thousands_sep;
	const char	*mon_grouping;
	const char	*positive_sign;
	const char	*negative_sign;
	const char	int_frac_digits;
	const char	frac_digits;
	const char	p_cs_precedes;
	const char	p_sep_by_space;
	const char	n_cs_precedes;
	const char	n_sep_by_space;
	const char	p_sign_posn;
	const char	n_sign_posn;
};

#define	LC_ALL		0
#define	LC_COLLATE	1
#define	LC_CTYPE	2
#define	LC_MONETARY	3
#define	LC_NUMERIC	4
#define	LC_TIME		5
#define LC_MESSAGES	6
#define	_LC_LAST	7		/* marks end */

__BEGIN_DECLS
extern int	locale_is_utf8;

struct lconv	*localeconv(void);
char		*setlocale(int, const char *);
__END_DECLS

#endif /* _LOCALE_H_ */
