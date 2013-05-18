/* $MirOS: src/kern/include/libckern.h,v 1.4 2007/02/06 23:32:56 tg Exp $ */

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
#ifndef EOF
#define EOF		(-1)
#endif
#endif /* !_STANDALONE && !_WCHAR_H_ */

__BEGIN_DECLS
size_t strlen(const char *);
__END_DECLS

#if !defined(_STANDALONE) && !defined(_WCHAR_H_)
__BEGIN_DECLS
size_t wcslen(const wchar_t *);
__END_DECLS

/* initialise/set/reset a mbstate_t to empty */
#define mbsreset(ps)	do {			\
		mbstate_t *__WC_s = (ps);	\
		if (ps != NULL)			\
			ps->count = 0;		\
	} while (0)
/* roll back the middle char of a mis-done 3-byte mb->wc conversion */
#define mbrtowc_rollback(ps)	__extension__({		\
		const mbstate_t *__WC_s = (ps);		\
		int __WC_rv = EOF;			\
		if (__WC_s->count == 1 &&		\
		    __WC_s->value >= 0x20)		\
			__WC_rv = 0x80 |		\
			    (__WC_s->value & 0x3F);	\
		(__WC_rv);				\
	})
#endif

#ifndef __LIBCKERN_HAVE_ADLER32_DECL
#define __LIBCKERN_HAVE_ADLER32_DECL
__BEGIN_DECLS
extern u_long adler32(u_long, const uint8_t *, unsigned);
__END_DECLS
#endif

#endif
