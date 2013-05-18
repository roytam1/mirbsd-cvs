/* $MirOS: src/include/wctype.h,v 1.5 2006/06/01 23:00:41 tg Exp $ */

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

extern const uint16_t * const mir18n_caseconv_tolower[0x100];
extern const uint16_t * const mir18n_caseconv_toupper[0x100];
__END_DECLS

#define iswalnum(x)	iswctype((x), _ctp_alnum)
#define iswalpha(x)	iswctype((x), _ctp_alpha)
#define iswblank(x)	iswctype((x), _ctp_blank)
#define iswcntrl(x)	iswctype((x), _ctp_cntrl)
#define iswdigit(x)	iswctype((x), _ctp_digit)
#define iswgraph(x)	iswctype((x), _ctp_graph)
#define iswlower(x)	iswctype((x), _ctp_lower)
#define iswprint(x)	iswctype((x), _ctp_print)
#define iswpunct(x)	iswctype((x), _ctp_punct)
#define iswspace(x)	iswctype((x), _ctp_space)
#define iswupper(x)	iswctype((x), _ctp_upper)
#define iswxdigit(x)	iswctype((x), _ctp_xdigit)
#define towlower(x)	towctrans((x), mir18n_caseconv_tolower)
#define towupper(x)	towctrans((x), mir18n_caseconv_toupper)

#endif
