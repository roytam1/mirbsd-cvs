/* $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $ */

/*-
 * Copyright (c) 2008
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

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
void __main(void);
int bcmp(const void *, const void *, size_t)
    __attribute__((bounded (string, 1, 3)))
    __attribute__((bounded (string, 2, 3)));
void bzero(void *, size_t)
    __attribute__((bounded (string, 1, 2)));
int ffs(int);
void *memchr(const void *, int, size_t)
    __attribute__((bounded (string, 1, 3)));
int memcmp(const void *, const void *, size_t)
    __attribute__((bounded (string, 1, 3)))
    __attribute__((bounded (string, 2, 3)));
void *memset(void *, int, size_t)
    __attribute__((bounded (string, 1, 3)));
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
size_t strlcat(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));
size_t strlcpy(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));
size_t strlen(const char *);
size_t strxfrm(char *, const char *, size_t)
    __attribute__((bounded (string, 1, 3)));

int wcscmp(const wchar_t *, const wchar_t *);
int wcscoll(const wchar_t *, const wchar_t *);
size_t wcslcat(wchar_t *, const wchar_t *, size_t);
size_t wcslcpy(wchar_t *, const wchar_t *, size_t);
size_t wcslen(const wchar_t *);
size_t wcsxfrm(wchar_t *, const wchar_t *, size_t);
__END_DECLS

/* initialise/set/reset a mbstate_t to empty */
#define mbsreset(ps) do {				\
	mbstate_t *__WC_s = (ps);			\
	if (ps != NULL)					\
		ps->count = 0;				\
} while (0)

/* XXX what about other compilers? */
#ifdef __GNUC__

/* roll back the middle char of a mis-done 3-byte mb->wc conversion */
#define mbrtowc_rollback(ps) __extension__({		\
	const mbstate_t *__WC_s = (ps);			\
	int __WC_rv = EOF;				\
	if (__WC_s->count == 1 &&			\
	    __WC_s->value >= 0x20)			\
		__WC_rv = 0x80 |			\
		    (__WC_s->value & 0x3F);		\
	(__WC_rv);					\
})

#define imax(a,b) __extension__({			\
	int imax_a = (a), imax_b = (b);			\
	(imax_a > imax_b ? imax_a : imax_b);		\
})
#define imin(a,b) __extension__({			\
	int imin_a = (a), imin_b = (b);			\
	(imin_a < imin_b ? imin_a : imin_b);		\
})
#define lmax(a,b) __extension__({			\
	long lmax_a = (a), lmax_b = (b);		\
	(lmax_a > lmax_b ? lmax_a : lmax_b);		\
})
#define lmin(a,b) __extension__({			\
	long lmin_a = (a), lmin_b = (b);		\
	(lmin_a < lmin_b ? lmin_a : lmin_b);		\
})
#define max(a,b) __extension__({			\
	u_int max_a = (a), max_b = (b);			\
	(max_a > max_b ? max_a : max_b);		\
})
#define min(a,b) __extension__({			\
	u_int min_a = (a), min_b = (b);			\
	(min_a < min_b ? min_a : min_b);		\
})
#define ulmax(a,b) __extension__({			\
	u_long ulmax_a = (a), ulmax_b = (b);		\
	(ulmax_a > ulmax_b ? ulmax_a : ulmax_b);	\
})
#define ulmin(a,b) __extension__({			\
	u_long ulmin_a = (a), ulmin_b = (b);		\
	(ulmin_a < ulmin_b ? ulmin_a : ulmin_b);	\
})
#define abs(j) __extension__({				\
	int abs_j = (j);				\
	(abs_j < 0 ? -abs_j : abs_j);			\
})

#endif /* __GNUC__ */

#ifndef __LIBCKERN_HAVE_ADLER32_DECL
#define __LIBCKERN_HAVE_ADLER32_DECL
__BEGIN_DECLS
extern u_long adler32(u_long, const uint8_t *, unsigned);
__END_DECLS
#endif

#endif
