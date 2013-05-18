/* $MirOS: src/kern/include/libckern.h,v 1.1 2007/02/06 18:58:06 tg Exp $ */

#ifndef __LIBCKERN_H_
#define __LIBCKERN_H_

#include <sys/types.h>

#if !defined(_STANDALONE) && !defined(_WCHAR_H_)
typedef __WCHAR_TYPE__	wchar_t;
typedef __WINT_TYPE__	wint_t;
typedef struct {
	unsigned int count:2;
	unsigned int value:12;	/* 10 for mbstowcs, 12 for wcstombs */
} __attribute__((packed)) mbstate_t;

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
