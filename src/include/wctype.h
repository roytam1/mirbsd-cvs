/* $MirOS: contrib/code/libhaible/wctype.h,v 1.7 2006/06/01 21:42:59 tg Exp $ */

#ifndef	_WCTYPE_H_
#define	_WCTYPE_H_

#include <wchar.h>

typedef const uint16_t * const *wctrans_t;

__BEGIN_DECLS
int	iswalnum(wint_t);
int	iswalpha(wint_t);
int	iswblank(wint_t);
int	iswcntrl(wint_t);
int	iswdigit(wint_t);
int	iswgraph(wint_t);
int	iswlower(wint_t);
int	iswprint(wint_t);
int	iswpunct(wint_t);
int	iswspace(wint_t);
int	iswupper(wint_t);
int	iswxdigit(wint_t);
int	iswctype(wint_t, wctype_t);
wint_t	towctrans(wint_t, wctrans_t);
wint_t	towlower(wint_t);
wint_t	towupper(wint_t);
wctrans_t wctrans(const char *);
__END_DECLS

#endif
