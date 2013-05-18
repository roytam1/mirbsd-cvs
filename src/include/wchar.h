/* $MirOS: src/include/wchar.h,v 1.16 2007/02/07 17:34:05 tg Exp $ */

/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
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

#ifndef	_WCHAR_H_
#define	_WCHAR_H_

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#if !defined(_GCC_WCHAR_T) && !defined(__cplusplus)
#define	_GCC_WCHAR_T
typedef	__WCHAR_TYPE__	wchar_t;
#endif

#if !defined(_GCC_WINT_T)
#define	_GCC_WINT_T
typedef	__WINT_TYPE__	wint_t;
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

typedef unsigned int wctype_t;
typedef struct {
	unsigned int count:2;
	unsigned int value:12;	/* 10 for mbstowcs, 12 for wcstombs */
} __attribute__((packed)) mbstate_t;

#undef WCHAR_MIN
#define	WCHAR_MIN		0
#undef WCHAR_MAX
#define	WCHAR_MAX		0xFFFDU
#undef WEOF
#define	WEOF			0xFFFFU

__BEGIN_DECLS
wint_t	btowc(int);
wint_t	fgetwc(FILE *);
wchar_t	*fgetws(wchar_t *__restrict__, int, FILE *__restrict__);
wint_t	fputwc(wchar_t, FILE *);
int	fputws(const wchar_t *__restrict__, FILE *__restrict__);
int	fwide(FILE *, int);
wint_t	getwc(FILE *);
wint_t	getwchar(void);
size_t	mbrlen(const char *__restrict__, size_t, mbstate_t *__restrict__);
size_t	mbrtowc(wchar_t *__restrict__, const char *__restrict__, size_t,
	    mbstate_t *__restrict__);
int	mbsinit(const mbstate_t *);
size_t	mbslen(const char *);
#if __OPENBSD_VISIBLE
size_t	mbsnrtowcs(wchar_t *__restrict__, const char **__restrict__,
	    size_t, size_t, mbstate_t *__restrict__);
#endif
size_t	mbsrtowcs(wchar_t *__restrict__, const char **__restrict__, size_t,
	    mbstate_t *__restrict__);
wint_t	putwc(wchar_t, FILE *);
wint_t	putwchar(wchar_t);
wint_t	ungetwc(wint_t, FILE *);
size_t	wcrtomb(char *__restrict__, wchar_t, mbstate_t *__restrict__);
int	wcscasecmp(const wchar_t *, const wchar_t *);
wchar_t	*wcscat(wchar_t *__restrict__, const wchar_t *__restrict__);
wchar_t	*wcschr(const wchar_t *, wchar_t);
int	wcscmp(const wchar_t *, const wchar_t *);
int	wcscoll(const wchar_t *, const wchar_t *);
wchar_t	*wcscpy(wchar_t *__restrict__, const wchar_t *__restrict__);
size_t	wcscspn(const wchar_t *, const wchar_t *);
wchar_t *wcsdup(const wchar_t *);
size_t	wcsftime(wchar_t *__restrict__, size_t, const wchar_t *__restrict__,
	    const struct tm *__restrict__);
size_t	wcslcat(wchar_t *, const wchar_t *, size_t);
size_t	wcslcpy(wchar_t *, const wchar_t *, size_t);
size_t	wcslen(const wchar_t *);
int	wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
wchar_t	*wcsncat(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
int	wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t	*wcsncpy(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
#if __OPENBSD_VISIBLE
size_t	wcsnrtombs(char *__restrict__, const wchar_t **__restrict__,
	    size_t, size_t, mbstate_t *__restrict__);
#endif
wchar_t	*wcspbrk(const wchar_t *, const wchar_t *);
wchar_t	*wcsrchr(const wchar_t *, wchar_t);
size_t	wcsrtombs(char *__restrict__, const wchar_t **__restrict__, size_t,
	    mbstate_t *__restrict__);
size_t	wcsspn(const wchar_t *, const wchar_t *);
wchar_t	*wcsstr(const wchar_t *__restrict__, const wchar_t *__restrict__);
double	wcstod(const wchar_t *__restrict__, wchar_t **__restrict__);
float	wcstof(const wchar_t *__restrict__, wchar_t **__restrict__);
wchar_t	*wcstok(wchar_t *__restrict__, const wchar_t *__restrict__,
	    wchar_t **__restrict__);
long	wcstol(const wchar_t *__restrict__, wchar_t **__restrict__, int);
long double wcstold(const wchar_t *__restrict__, wchar_t **__restrict__);
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    defined(_ISOC99_SOURCE) || (__STDC_VERSION__ - 0) > 199901L
/* LONGLONG */
long long wcstoll(const wchar_t *__restrict__, wchar_t **__restrict__, int);
#endif
unsigned long wcstoul(const wchar_t *__restrict__, wchar_t **__restrict__,
	    int);
#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || \
    defined(_ISOC99_SOURCE) || (__STDC_VERSION__ - 0) > 199901L
/* LONGLONG */
unsigned long long wcstoull(const wchar_t *__restrict__,
	    wchar_t **__restrict__, int);
#endif
wchar_t	*wcswcs(const wchar_t *, const wchar_t *);
int	wcswidth(const wchar_t *, size_t);
size_t	wcsxfrm(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
int	wctob(wint_t);
wctype_t wctype(const char *);
int	wcwidth(wchar_t);
wchar_t	*wmemchr(const wchar_t *, wchar_t, size_t);
int	wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t	*wmemcpy(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
wchar_t	*wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t	*wmemset(wchar_t *, wchar_t, size_t);

/* these functions are currently not implemented in libc */
#if 0
int	fwprintf(FILE * __restrict__, const wchar_t * __restrict__, ...);
int	fwscanf(FILE *__restrict__, const wchar_t *__restrict__, ...);
int	swprintf(wchar_t * __restrict__, size_t, const wchar_t * __restrict__,
	    ...);
int	swscanf(const wchar_t *__restrict__, const wchar_t *__restrict__, ...);
int	vfwprintf(FILE * __restrict__, const wchar_t * __restrict__,
	    _BSD_VA_LIST_);
int	vfwscanf(FILE *__restrict__, const wchar_t *__restrict__,
	    _BSD_VA_LIST_);
int	vswprintf(wchar_t * __restrict__, const wchar_t * __restrict__,
	    _BSD_VA_LIST_);
int	vswscanf(const wchar_t *__restrict__, const wchar_t *__restrict__,
	    _BSD_VA_LIST_);
int	vwprintf(const wchar_t * __restrict__, _BSD_VA_LIST_);
int	vwscanf(const wchar_t *__restrict__, _BSD_VA_LIST_);
int	wprintf(const wchar_t * __restrict__, ...);
int	wscanf(const wchar_t *__restrict__, ...);
#endif
__END_DECLS

#define getwc(f)	fgetwc(f)
#define getwchar()	getwc(stdin)
#define putwc(wc, f)	fputwc((wc), (f))
#define putwchar(wc)	putwc((wc), stdout)

#ifdef __GNUC__
#define btowc(c)	__extension__({			\
	wint_t __WC_tmp = (c);				\
							\
	(__WC_tmp > 0x7F ? WEOF : __WC_tmp);		\
})
#define mblen(s,n)	__extension__({			\
	mbstate_t __WC_ps = { 0, 0 };			\
	int __WC_rv;					\
							\
	(((__WC_rv = mbrtowc(NULL, (s), (n),		\
	    &__WC_ps)) < 0) ? -1 : __WC_rv);		\
})
#define mbsinit(c)	__extension__({			\
	const mbstate_t *__WC_ps = (c);			\
							\
	(__WC_ps == NULL ? -1 :				\
	    __WC_ps->count == 0 ? 1 : 0);		\
})
#define mbslen(c)	__extension__({			\
	const uint8_t *__WC_s = (c);			\
	size_t __WC_num = 0;				\
							\
	while (*__WC_s) {				\
		if ((*__WC_s & 0xC0) != 0x80)		\
			++__WC_num;			\
		++__WC_s;				\
	}						\
	(__WC_num);					\
})
#define mbstowcs(pwcs,s,n)	__extension__({		\
	mbstate_t __WC_ps = { 0, 0 };			\
	const char *__WC_sb = (s);			\
							\
	(mbsrtowcs((pwcs), &__WC_sb, (n), &__WC_ps));	\
})
#define mbtowc(pwc,s,n)	__extension__({			\
	mbstate_t __WC_ps = { 0, 0 };			\
	int __WC_rv;					\
							\
	(((__WC_rv = mbrtowc((pwc), (s), (n),		\
	    &__WC_ps)) < 0) ? -1 : __WC_rv);		\
})
#define wcstombs(s,pwcs,n)	__extension__({		\
	mbstate_t __WC_ps = { 0, 0 };			\
	const wchar_t *__WC_sb = (pwcs);		\
							\
	(wcsrtombs((s), &__WC_sb, (n), &__WC_ps));	\
})
#define wcswidth(s,n)	__extension__({			\
	int __WC_width = 0, __WC_i, __WC_n = (n);	\
	const wchar_t *__WC_s = (s);			\
							\
	while (__WC_n--) {				\
		if (*__WC_s == L'\0')			\
			break;				\
		if ((__WC_i = wcwidth(*__WC_s))	< 0) {	\
			__WC_width = -1;		\
			break;				\
		}					\
		__WC_width += __WC_i;			\
		__WC_s++;				\
	}						\
	(__WC_width);					\
})
#define wctob(c)	__extension__({			\
	wint_t __WC_tmp = (c);				\
							\
	(__WC_tmp > 0x7F ? EOF : (int)__WC_tmp);	\
})
#define wctomb(s,c)	__extension__({			\
	mbstate_t __WC_ps = { 0, 0 };			\
	char *__WC_s = (s);				\
							\
	(__WC_s ? wcrtomb(__WC_s, (c), &__WC_ps) : 0);	\
})
/* initialise/set/reset a mbstate_t to empty */
#define mbsreset(ps)	do {				\
	mbstate_t *__WC_s = (ps);			\
							\
	if (__WC_s != NULL)				\
		__WC_s->count = 0;			\
} while (0)
/* roll back the middle char of a mis-done 3-byte mb->wc conversion */
#define mbrtowc_rollback(ps)	__extension__({		\
	const mbstate_t *__WC_s = (ps);			\
	int __WC_rv = EOF;				\
							\
	if (__WC_s->count == 1 &&			\
	    __WC_s->value >= 0x20)			\
		__WC_rv = 0x80 |			\
		    (__WC_s->value & 0x3F);		\
	(__WC_rv);					\
})
#endif

#endif
