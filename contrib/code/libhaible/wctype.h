/* $MirOS: contrib/code/libhaible/wctype.h,v 1.5 2006/05/30 11:34:22 tg Exp $ */

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
