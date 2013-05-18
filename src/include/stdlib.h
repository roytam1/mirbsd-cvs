/**	$MirOS: src/include/stdlib.h,v 1.18 2008/04/06 16:35:16 tg Exp $ */
/*	$OpenBSD: stdlib.h,v 1.34 2005/05/27 17:45:56 millert Exp $	*/
/*	$NetBSD: stdlib.h,v 1.25 1995/12/27 21:19:08 jtc Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdlib.h	5.13 (Berkeley) 6/4/91
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <machine/ansi.h>

#if !defined(_ANSI_SOURCE)	/* for quad_t, etc. */
#include <sys/types.h>
#endif

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__	size_t;
#endif

#if !defined(_GCC_WCHAR_T) && !defined(__cplusplus)
#define	_GCC_WCHAR_T
typedef	__WCHAR_TYPE__	wchar_t;
#endif

typedef struct {
	int quot;		/* quotient */
	int rem;		/* remainder */
} div_t;

typedef struct {
	long quot;		/* quotient */
	long rem;		/* remainder */
} ldiv_t;

#if !defined(_ANSI_SOURCE)
typedef struct {
	quad_t quot;		/* quotient */
	quad_t rem;		/* remainder */
} qdiv_t;
#endif


#ifndef NULL
#ifdef 	__GNUG__
#define	NULL	__null
#elif defined(lint)
#define	NULL	0
#else
#define	NULL	((void *)((__PTRDIFF_TYPE__)0UL))
#endif
#endif

#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0

#define	RAND_MAX	0x7fffffff

/* maximum length of a multibyte character sequence (all locales) */
/*
 * Note: we internally use UCS-2 which yields a maximum of 3, but
 * due to the brain-dead specification of e.g. wcrtomb(3), 2 more
 * bytes (MAX - 1) can be stored due to old mbstate_t processing.
 */
#undef MB_LEN_MAX
#define MB_LEN_MAX	5	/* 3 (UCS-2) * 2 - 1 */

/* maximum length of a multibyte character sequence (current locale) */
#undef MB_CUR_MAX
#define MB_CUR_MAX	5

#include <sys/cdefs.h>

/*
 * Some header files may define an abs macro.
 * If defined, undef it to prevent a syntax error and issue a warning.
 */
#ifdef abs
#undef abs
#warning abs macro collides with abs() prototype, undefining
#endif

__BEGIN_DECLS
__dead void	 abort(void);
int	 abs(int);
int	 atexit(void (*)(void));
double	 atof(const char *);
int	 atoi(const char *);
long	 atol(const char *);
/* LONGLONG */
long long atoll(const char *);
void	*bsearch(const void *, const void *, size_t, size_t,
	    int (*)(const void *, const void *));
void	*calloc(size_t, size_t);
div_t	 div(int, int);
char	*ecvt(double, int, int *, int *);
__dead void	 exit(int);
__dead void	 _Exit(int);
char	*fcvt(double, int, int *, int *);
void	 free(void *);
char	*gcvt(double, int, char *);
char	*getenv(const char *);
long	 labs(long);
ldiv_t	 ldiv(long, long);
/* LONGLONG */
long long
	 llabs(long long);
void	*malloc(size_t);
char	*mkdtemp(char *);
int	 mkstemp(char *);
int	 mkstemps(char *, int);
char	*mktemp(char *);
void	 qsort(void *, size_t, size_t, int (*)(const void *, const void *));
int	 rand(void);
int	 rand_r(unsigned int *);
void	*realloc(void *, size_t);
void	 srand(unsigned);
double	 strtod(const char *, char **);
long	 strtol(const char *, char **, int);
/* LONGLONG */
long long
	 strtoll(const char *, char **, int);
/* LONGLONG */
long long
	 strtonum(const char *, long long, long long, const char **);
unsigned long
	 strtoul(const char *, char **, int);
/* LONGLONG */
unsigned long long
	 strtoull(const char *, char **, int);
int	 system(const char *);

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
#if defined(alloca) && (alloca == __builtin_alloca) && (__GNUC__ < 2)
void  *alloca(int);     /* built-in for gcc */
#else
void  *alloca(size_t);
#endif /* __GNUC__ */

char	*getbsize(int *, long *);
char	*cgetcap(char *, const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, char **, const char *);
int	 cgetfirst(char **, char **);
int	 cgetmatch(char *, const char *);
int	 cgetnext(char **, char **);
int	 cgetnum(char *, const char *, long *);
int	 cgetset(const char *);
int	 cgetusedb(int);
int	 cgetstr(char *, const char *, char **);
int	 cgetustr(char *, const char *, char **);

int	 daemon(int, int);
char	*devname(int, int);
int	 getloadavg(double [], int);

long	 a64l(const char *);
char	*l64a(long);

void	 cfree(void *);

#ifndef _GETOPT_DEFINED_
#define _GETOPT_DEFINED_
int	 getopt(int, char * const *, const char *);
extern	 char *optarg;			/* getopt(3) external variables */
extern	 int opterr;
extern	 int optind;
extern	 int optopt;
extern	 int optreset;
int	 getsubopt(char **, char * const *, char **);
extern	 char *suboptarg;		/* getsubopt(3) external variable */
#endif /* _GETOPT_DEFINED_ */

int	 heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
int	 mergesort(void *, size_t, size_t, int (*)(const void *, const void *));
int	 radixsort(const unsigned char **, int, const unsigned char *,
	    unsigned);
int	 sradixsort(const unsigned char **, int, const unsigned char *,
	    unsigned);

char	*initstate(unsigned int, char *, size_t)
		__attribute__((__bounded__ (__string__,2,3)));
long	 random(void);
char	*realpath(const char *, char *);
char	*setstate(const char *);
void	 srandom(unsigned int);
void	 srandomdev(void);

int	 putenv(const char *);
int	 setenv(const char *, const char *, int);
int	 unsetenv(const char *);
void	 setproctitle(const char *, ...)
	__attribute__((__format__ (__printf__, 1, 2)));

quad_t	 qabs(quad_t);
qdiv_t	 qdiv(quad_t, quad_t);
quad_t	 strtoq(const char *, char **, int);
u_quad_t strtouq(const char *, char **, int);

double	 drand48(void);
double	 erand48(unsigned short[3]);
long	 jrand48(unsigned short[3]);
void	 lcong48(unsigned short[7]);
long	 lrand48(void);
long	 mrand48(void);
long	 nrand48(unsigned short[3]);
unsigned short *seed48(unsigned short[3]);
void	 srand48(long);

u_int32_t arc4random(void);
void	arc4random_stir(void);
void	arc4random_addrandom(unsigned char *, int)
	__attribute__((bounded (string, 1, 2)));
void	arc4random_push(int);
uint32_t arc4random_pushb(const void *, size_t)
	__attribute__((bounded (string, 1, 2)));
#undef arc4random_pushk
#define arc4random_pushk arc4random_pushk
uint32_t arc4random_pushk(const void *, size_t)
	__attribute__((bounded (string, 1, 2)));

void	setprogname(const char *);
const char *getprogname(void);
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

int	mblen(const char *, size_t);
size_t	mbstowcs(wchar_t *__restrict__, const char *__restrict__, size_t);
int	mbtowc(wchar_t *__restrict__, const char *__restrict__, size_t);
size_t	wcstombs(char *__restrict__, const wchar_t *__restrict__, size_t);
int	wctomb(char *, const wchar_t);
__END_DECLS

#if defined(_SVID_SOURCE) && !defined(__STRICT_ANSI__)
__BEGIN_DECLS
int rpmatch(const char *);
__END_DECLS
#endif

#endif /* _STDLIB_H_ */
