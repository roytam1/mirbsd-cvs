/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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

#ifdef	_BSD_WCHAR_T_
/* in C++, wchar_t is a built-in type */
#ifndef __cplusplus
typedef	_BSD_WCHAR_T_	wchar_t;
#endif
#undef	_BSD_WCHAR_T_
#endif

#ifdef	_BSD_WINT_T_
typedef	_BSD_WINT_T_	wint_t;
#undef	_BSD_WINT_T_
#endif

typedef unsigned long int wctype_t;
typedef struct {
	unsigned int count:2;
	unsigned int value:12;	/* 10 for mbstowcs, 12 for wcstombs */
} __attribute__((packed)) mbstate_t;

#undef	WCHAR_MIN
#undef	WCHAR_MAX
#undef	WEOF
#define	WCHAR_MIN		0
#define	WCHAR_MAX		0xFFFDU
#define	WEOF			0xFFFFU

__BEGIN_DECLS
wint_t	btowc(int);
wint_t	fgetwc(FILE *);
wchar_t	*fgetws(wchar_t *__restrict__, int, FILE *__restrict__);
wint_t	fputwc(wchar_t, FILE *);
int	fputws(const wchar_t *__restrict__, FILE *__restrict__);
int	fwide(FILE *, int);
int	fwprintf(FILE * __restrict__, const wchar_t * __restrict__, ...);
int	fwscanf(FILE *__restrict__, const wchar_t *__restrict__, ...);
wint_t	getwc(FILE *);
wint_t	getwchar(void);
size_t	mbrlen(const char *__restrict__, size_t, mbstate_t *__restrict__);
size_t	mbrtowc(wchar_t *__restrict__, const char *__restrict__, size_t,
	    mbstate_t *__restrict__);
int	mbsinit(const mbstate_t *);
size_t	mbsrtowcs(wchar_t *__restrict__, const char **__restrict__, size_t,
	    mbstate_t *__restrict__);
wint_t	putwc(wchar_t, FILE *);
wint_t	putwchar(wchar_t);
int	swprintf(wchar_t * __restrict__, size_t, const wchar_t * __restrict__,
	    ...);
int	swscanf(const wchar_t *__restrict__, const wchar_t *__restrict__, ...);
wint_t	ungetwc(wint_t, FILE *);
int	vfwprintf(FILE * __restrict__, const wchar_t * __restrict__,
	    _BSD_VA_LIST_);
int	vfwscanf(FILE *__restrict__, const wchar_t *__restrict__, _BSD_VA_LIST_);
int	vswprintf(wchar_t * __restrict__, const wchar_t * __restrict__,
	    _BSD_VA_LIST_);
int	vswscanf(const wchar_t *__restrict__, const wchar_t *__restrict__,
	    _BSD_VA_LIST_);
int	vwprintf(const wchar_t * __restrict__, _BSD_VA_LIST_);
int	vwscanf(const wchar_t *__restrict__, _BSD_VA_LIST_);
size_t	wcrtomb(char *__restrict__, wchar_t, mbstate_t *__restrict__);
wchar_t	*wcscat(wchar_t *__restrict__, const wchar_t *__restrict__);
wchar_t	*wcschr(const wchar_t *, wchar_t);
int	wcscmp(const wchar_t *, const wchar_t *);
int	wcscoll(const wchar_t *, const wchar_t *);
wchar_t	*wcscpy(wchar_t *__restrict__, const wchar_t *__restrict__);
size_t	wcscspn(const wchar_t *, const wchar_t *);
size_t	wcsftime(wchar_t *__restrict__, size_t, const wchar_t *__restrict__,
	    const struct tm *__restrict__);
size_t	wcslcat(wchar_t *, const wchar_t *, size_t);
size_t	wcslcpy(wchar_t *, const wchar_t *, size_t);
size_t	wcslen(const wchar_t *);
wchar_t	*wcsncat(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
int	wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t	*wcsncpy(wchar_t *__restrict__, const wchar_t *__restrict__, size_t);
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
int	wprintf(const wchar_t * __restrict__, ...);
int	wscanf(const wchar_t *__restrict__, ...);
__END_DECLS

#define getwc(f) fgetwc(f)
#define getwchar() getwc(stdin)
#define putwc(wc, f) fputwc((wc), (f))
#define putwchar(wc) putwc((wc), stdout)

#endif
