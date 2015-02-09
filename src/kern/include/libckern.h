/* $MirOS: src/kern/include/libckern.h,v 1.38 2014/11/30 21:30:56 tg Exp $ */

/*-
 * Copyright (c) 2008, 2010, 2011, 2013, 2014, 2015
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

#ifdef __MirBSD__

#ifndef NULL
#ifdef __GNUG__
#define	NULL			__null
#elif defined(lint) || defined(__cplusplus)
#define	NULL			0
#else
#define	NULL			((void *)((__PTRDIFF_TYPE__)0UL))
#endif
#endif

#ifndef __IN_MKDEP
/* makedepend may not define the constants we are checking for */
#if __WCHAR_MAX__ != 65535U
#error GCC __WCHAR_MAX__ does not indicate UCS-2
#endif
#ifndef __STDC_ISO_10646__
#error This code assumes that wchar_t is UCS-2HE
#endif
#endif /* !__IN_MKDEP */

#if !defined(_GCC_WCHAR_T) && !defined(__cplusplus)
#define	_GCC_WCHAR_T
typedef	__WCHAR_TYPE__	wchar_t;
#endif

#if !defined(_GCC_WINT_T)
#define	_GCC_WINT_T
typedef	__WINT_TYPE__	wint_t;
#endif

#if !defined(_GCC_MBSTATE_T)
#define	_GCC_MBSTATE_T
typedef struct {
	unsigned int count:2;
	unsigned int value:12;
} __attribute__((__packed__)) mbstate_t;
#endif

/**
 * An arcfour_status is hereby defined as carrying
 * 212 octets (1696 bit) of entropic state, whereas
 * S contains 210 octets and 3 or 4 additioinal bit,
 * i is another 8 bit, and j adds enough to make up
 * for the 4-5 bit of additional entropy we assume.
 */
struct arcfour_status {
	uint8_t S[256];
	uint8_t i;
	uint8_t j;
};

#undef WCHAR_MIN
#define WCHAR_MIN	0
#undef WCHAR_MAX
#define WCHAR_MAX	0xFFFDU
#undef WEOF
#define WEOF		0xFFFFU

#ifndef EOF
#define EOF		(-1)
#endif

#endif /* __MirBSD__ */

__BEGIN_DECLS
void __main(void);

void arc4random_roundhash(uint32_t *, uint8_t *, const void *, size_t)
    __attribute__((__bounded__(__minbytes__, 1, 128)))
    __attribute__((__bounded__(__buffer__, 3, 4)));
/* u_int32_t in the original API, but we pray they're the same */
uint32_t arc4random_uniform(uint32_t);

/* arcfour: base cipher */
void arcfour_init(struct arcfour_status *);
void arcfour_ksa(struct arcfour_status *, const uint8_t *, size_t)
    __attribute__((__bounded__(__buffer__, 2, 3)));
uint8_t arcfour_byte(struct arcfour_status *);

int bcmp(const void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void bcopy(const void *, void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void bzero(void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 2)));
void explicit_bzero(void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 2)));

int ffs(int);

void *memchr(const void *, int, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)));
int memcmp(const void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void *memcpy(void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void memhexdump(const void *, size_t, size_t);
void *memmove(void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void *mempcpy(void *, const void *, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)))
    __attribute__((__bounded__(__buffer__, 2, 3)));
void *memset(void *, int, size_t)
    __attribute__((__bounded__(__buffer__, 1, 3)));

size_t optu16to8(char *, wchar_t, mbstate_t *)
    __attribute__((__bounded__(__minbytes__, 1, 5)));
size_t optu8to16(wchar_t *, const char *, size_t, mbstate_t *)
    __attribute__((__bounded__(__string__, 2, 3)));

int strcasecmp(const char *, const char *);
char *strchr(const char *, int);
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
size_t strlcat(char *, const char *, size_t)
    __attribute__((__bounded__(__string__, 1, 3)));
size_t strlcpy(char *, const char *, size_t)
    __attribute__((__bounded__(__string__, 1, 3)));
size_t strlen(const char *);
int strncasecmp(const char *, const char *, size_t);
int strncmp(const char *, const char *, size_t);
char *strncpy(char *, const char *, size_t)
    __attribute__((__bounded__(__string__, 1, 3)));
char *strrchr(const char *, int);
size_t strxfrm(char *, const char *, size_t)
    __attribute__((__bounded__(__string__, 1, 3)));

#ifdef _KERN_HOSTED
size_t wcrtomb(char *, wchar_t, mbstate_t *)
    __attribute__((__bounded__(__minbytes__, 1, 5)));
#endif
int wcscasecmp(const wchar_t *, const wchar_t *);
int wcscmp(const wchar_t *, const wchar_t *);
int wcscoll(const wchar_t *, const wchar_t *);
size_t wcslcat(wchar_t *, const wchar_t *, size_t);
size_t wcslcpy(wchar_t *, const wchar_t *, size_t);
size_t wcslen(const wchar_t *);
int wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
size_t wcsxfrm(wchar_t *, const wchar_t *, size_t);
__END_DECLS

#ifndef iswoctet
#define iswoctet(wc)	(((wchar_t)(wc) & 0xFF80) == 0xEF80)
#endif

#ifdef __MirBSD__
/* initialise/set/reset a mbstate_t to empty */
#define mbsreset(ps) do {				\
	mbstate_t *__WC_s = (ps);			\
	if (ps != NULL)					\
		ps->count = 0;				\
} while (0)
#endif /* __MirBSD__ */

/* XXX what about other compilers? */
#ifdef __GNUC__

#ifdef __MirBSD__
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
#endif /* __MirBSD__ */

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

#ifndef _STDLIB_H_abs_DEFINED
#undef abs
__BEGIN_DECLS
int abs(int);
__END_DECLS
#define _STDLIB_H_abs_DEFINED
#define abs(j) __extension__({				\
	int abs_j = (j);				\
	(abs_j < 0 ? -abs_j : abs_j);			\
})
#endif

#endif /* __GNUC__ */

#ifndef __LIBCKERN_HAVE_ADLER32_DECL
#define __LIBCKERN_HAVE_ADLER32_DECL
__BEGIN_DECLS
extern u_long adler32(u_long, const uint8_t *, unsigned);
__END_DECLS
#endif

#endif
