/* $MirOS: src/kern/c/libckern.h,v 1.1 2007/02/06 16:24:42 tg Exp $ */

#ifndef __LIBCKERN_H_
#define __LIBCKERN_H_

#include <sys/types.h>

#if !defined(_STANDALONE) && !defined(_WCHAR_H_)
typedef __WCHAR_TYPE__	wchar_t;
typedef __WINT_TYPE__	wint_t;

/* makedepend may not define __WCHAR_MAX__ */
#if defined(__WCHAR_MAX__) && (__WCHAR_MAX__ != 65535U)
#error GCC __WCHAR_MAX__ does not indicate UCS-2
#endif

#undef WCHAR_MIN
#define WCHAR_MIN	0
#undef WCHAR_MAX
#define WCHAR_MAX	0xFFFDU
#undef WEOF
#define WEOF		0xFFFFU
#endif /* !_STANDALONE && !_WCHAR_H_ */

__BEGIN_DECLS
size_t strlen(const char *);
__END_DECLS

#if !defined(_STANDALONE) && !defined(_WCHAR_H_)
size_t wcslen(const wchar_t *);
#endif

#endif
