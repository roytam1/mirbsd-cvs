/* $MirOS: src/kern/include/libckern.h,v 1.5 2007/03/02 01:57:06 tg Exp $ */

#ifndef __LIBCKERN_H_
#define __LIBCKERN_H_

#include <sys/types.h>

#if !defined(_WCHAR_H_)
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
#ifndef EOF
#define EOF		(-1)
#endif
#endif /* !_WCHAR_H_ */

__BEGIN_DECLS
size_t strlcat(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));
size_t strlcpy(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));
size_t strlen(const char *);
size_t strxfrm(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));

size_t wcslcat(wchar_t *, const wchar_t *, size_t);
size_t wcslcpy(wchar_t *, const wchar_t *, size_t);
size_t wcslen(const wchar_t *);
size_t wcsxfrm(wchar_t *, const wchar_t *, size_t);
__END_DECLS

/* initialise/set/reset a mbstate_t to empty */
#define mbsreset(ps) do {			\
	mbstate_t *__WC_s = (ps);		\
	if (ps != NULL)				\
		ps->count = 0;			\
} while (0)
/* roll back the middle char of a mis-done 3-byte mb->wc conversion */
#define mbrtowc_rollback(ps) __extension__({	\
	const mbstate_t *__WC_s = (ps);		\
	int __WC_rv = EOF;			\
	if (__WC_s->count == 1 &&		\
	    __WC_s->value >= 0x20)		\
		__WC_rv = 0x80 |		\
		    (__WC_s->value & 0x3F);	\
	(__WC_rv);				\
})

#ifndef __LIBCKERN_HAVE_ADLER32_DECL
#define __LIBCKERN_HAVE_ADLER32_DECL
__BEGIN_DECLS
extern u_long adler32(u_long, const uint8_t *, unsigned);
__END_DECLS
#endif

#endif
