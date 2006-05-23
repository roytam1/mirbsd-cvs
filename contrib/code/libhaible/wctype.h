/* $MirOS: contrib/code/libhaible/wctype.h,v 1.2 2006/05/23 11:26:46 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#ifndef	_WCTYPE_H_
#define	_WCTYPE_H_

#include <wchar.h>

#ifndef __BIT_TYPES_DEFINED__
#include <machine/types.h>
#endif

typedef const uint16_t * const *wctrans_t;

__BEGIN_DECLS
int	iswalnum(wint_t);
int	iswalpha(wint_t);
#ifdef notyet
int	iswblank(wint_t);
int	iswcntrl(wint_t);
int	iswdigit(wint_t);
int	iswgraph(wint_t);
#endif
int	iswlower(wint_t);
#ifdef notyet
int	iswprint(wint_t);
int	iswpunct(wint_t);
int	iswspace(wint_t);
#endif
int	iswupper(wint_t);
#ifdef notyet
int	iswxdigit(wint_t);
int	iswctype(wint_t, wctype_t);
#endif
wint_t	towctrans(wint_t, wctrans_t);
wint_t	towlower(wint_t);
wint_t	towupper(wint_t);
#ifdef notyet
wctrans_t wctrans(const char *);
#endif
__END_DECLS

#endif
