/* $MirOS: src/lib/libc/stdio/vfprintf.c,v 1.8 2008/08/02 00:57:30 tg Exp $ */

/*-
 * Copyright (c) 2007, 2008, 2010
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

#include <sys/types.h>

extern const uint8_t mbsd_digits_hex[17];
extern const uint8_t mbsd_digits_HEX[17];

/*	$OpenBSD: vfprintf.c,v 1.32 2005/08/08 08:05:36 espie Exp $ */
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
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
 */

/*
 * Actual printf innards.
 *
 * This code is large and complicated...
 */

#include <sys/mman.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>

#include "local.h"
#include "fvwrite.h"

__RCSID("$MirOS: src/lib/libc/stdio/vfprintf.c,v 1.8 2008/08/02 00:57:30 tg Exp $");

static void __find_arguments(const char *fmt0, va_list ap, va_list **argtable,
    size_t *argtablesiz);
static int __grow_type_table(unsigned char **typetable, int *tablesize);

/*
 * Flush out all the vectors defined by the given uio,
 * then reset it so that it can be reused.
 */
static int
__sprint(FILE *fp, struct __suio *uio)
{
	int err;

	if (uio->uio_resid == 0) {
		uio->uio_iovcnt = 0;
		return (0);
	}
	err = __sfvwrite(fp, uio);
	uio->uio_resid = 0;
	uio->uio_iovcnt = 0;
	return (err);
}

/*
 * Helper function for 'fprintf to unbuffered unix file': creates a
 * temporary buffer.  We only work on write-only files; this avoids
 * worries about ungetc buffers and so forth.
 */
static int
__sbprintf(FILE *fp, const char *fmt, va_list ap)
{
	int ret;
	FILE fake;
	struct __sfileext fakeext;
	unsigned char buf[BUFSIZ];

	_FILEEXT_SETUP(&fake, &fakeext);
	/* copy the important variables */
	fake._flags = fp->_flags & ~__SNBF;
	fake._file = fp->_file;
	fake._cookie = fp->_cookie;
	fake._write = fp->_write;

	/* set up the buffer */
	fake._bf._base = fake._p = buf;
	fake._bf._size = fake._w = sizeof(buf);
	fake._lbfsize = 0;	/* not actually used, but Just In Case */

	/* do the work, then copy any error status */
	ret = vfprintf(&fake, fmt, ap);
	if (ret >= 0 && fflush(&fake))
		ret = EOF;
	if (fake._flags & __SERR)
		fp->_flags |= __SERR;
	return (ret);
}


#ifdef FLOATING_POINT
#include <locale.h>
#include <math.h>
#include "floatio.h"

#define	BUF		(MAXEXP+MAXFRACT+1)	/* + decimal point */
#define	DEFPREC		6

static char *cvt(double, int, int, char *, int *, int, int *);
static int exponent(char *, int, int);

#else /* no FLOATING_POINT */
#define	BUF		40
#endif /* FLOATING_POINT */

#define STATIC_ARG_TBL_SIZE 8	/* Size of static argument table. */


/*
 * Macros for converting digits to letters and vice versa
 */
#define	to_digit(c)	((c) - '0')
#define is_digit(c)	((unsigned)to_digit(c) <= 9)
#define	to_char(n)	((n) + '0')

/*
 * Flags used during conversion.
 */
#define	ALT		0x001		/* alternate form */
#define	HEXPREFIX	0x002		/* add 0x or 0X prefix */
#define	LADJUST		0x004		/* left adjustment */
#define	LONGDBL		0x008		/* long double; unimplemented */
#define	LONGINT		0x010		/* long integer */
#define	QUADINT		0x020		/* quad integer */
#define	SHORTINT	0x040		/* short integer */
#define	ZEROPAD		0x080		/* zero (as opposed to blank) pad */
#define FPT		0x100		/* Floating point number */
#define PTRINT		0x200		/* (unsigned) ptrdiff_t */
#define SIZEINT		0x400		/* (signed) size_t */
#define CHARINT		0x800		/* (un)signed char */

int
vfprintf(FILE *fp, const char *fmt0, _BSD_VA_LIST_ ap)
{
	char *fmt;		/* format string */
	int ch;			/* character from fmt */
	int n, m, n2;		/* handy integers (short term usage) */
	char *cp;		/* handy char pointer (short term usage) */
	wchar_t *wcp;		/* handy wchar_t pointer (short term usage) */
	struct __siov *iovp;	/* for PRINT macro */
	int flags;		/* flags as above */
	int ret;		/* return value accumulator */
	int width;		/* width from format (%8d), or 0 */
	int prec;		/* precision from format (%.3d), or -1 */
	char sign;		/* sign prefix (' ', '+', '-', or \0) */
	wchar_t wc;
	mbstate_t ps;
#ifdef FLOATING_POINT
#if 0
	char *decimal_point = localeconv()->decimal_point;
#else
#define decimal_point		"."
#endif
	char softsign;		/* temporary negative sign for floats */
	double _double;		/* double precision arguments %[eEfgG] */
	int expt;		/* integer value of exponent */
	int expsize;		/* character count for expstr */
	int ndig;		/* actual number of digits returned by cvt */
	char expstr[7];		/* buffer for exponent string */
#endif

#ifdef __GNUC__			/* gcc has builtin quad type (long long) SOS */
#define	quad_t	  long long
#define	u_quad_t  unsigned long long
#endif

	u_quad_t _uquad;	/* integer arguments %[diouxX] */
	enum { OCT, DEC, HEX } base;/* base for [diouxX] conversion */
	int dprec;		/* a copy of prec if [diouxX], 0 otherwise */
	int realsz;		/* field size expanded by dprec */
	int size;		/* size of converted field or string */
	const uint8_t *xdigs;	/* digits for [xX] conversion */
#define NIOV 8
	struct __suio uio;	/* output information: summary */
	struct __siov iov[NIOV];/* ... and individual io vectors */
	char buf[BUF];		/* space for %[Ccm], %[diouxX], %[eEfgG] */
	char ox[2];		/* space for 0x hex-prefix */
	va_list *argtable;	/* args, built due to positional arg */
	va_list statargtable[STATIC_ARG_TBL_SIZE];
	size_t argtablesiz;
	int nextarg;		/* 1-based argument index */
	va_list orgap;		/* original argument pointer */
	char *mmapalloc = NULL;	/* something we need to munmap */
	size_t mmapalcsz = 0;	/* and its size */
	int origerrno;		/* errno on function entry */

	/*
	 * Choose PADSIZE to trade efficiency vs. size.  If larger printf
	 * fields occur frequently, increase PADSIZE and make the initialisers
	 * below longer.
	 */
#define	PADSIZE	16		/* pad chunk size */
	static char blanks[PADSIZE] =
	 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	static char zeroes[PADSIZE] =
	 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

	origerrno = errno;

	/*
	 * BEWARE, these 'goto error' on error, and PAD uses 'n'.
	 */
#define	ADDTORET(x) do {	\
	int oldret = ret;	\
	ret += (x);		\
	if (oldret > ret) {	\
		ret = EOF;	\
		errno = ERANGE;	\
		goto error;	\
	}			\
} while (0)
#define	PRINT(ptr, len) do { \
	iovp->iov_base = (ptr); \
	iovp->iov_len = (len); \
	uio.uio_resid += (len); \
	iovp++; \
	if (++uio.uio_iovcnt >= NIOV) { \
		if (__sprint(fp, &uio)) \
			goto error; \
		iovp = iov; \
	} \
} while (0)
#define	PAD(howmany, with) do { \
	if ((n = (howmany)) > 0) { \
		while (n > PADSIZE) { \
			PRINT(with, PADSIZE); \
			n -= PADSIZE; \
		} \
		PRINT(with, n); \
	} \
} while (0)
#define	FLUSH() do { \
	if (uio.uio_resid && __sprint(fp, &uio)) \
		goto error; \
	uio.uio_iovcnt = 0; \
	iovp = iov; \
} while (0)

	/*
	 * To extend shorts properly, we need both signed and unsigned
	 * argument extraction methods.
	 */
#define	SARG() \
	(flags&QUADINT ? GETARG(quad_t) : \
	    flags&LONGINT ? GETARG(long) : \
	    flags&PTRINT ? GETARG(ptrdiff_t) : \
	    flags&SIZEINT ? GETARG(ssize_t) : \
	    flags&SHORTINT ? (long)(short)GETARG(int) : \
	    flags&CHARINT ? (long)(signed char)GETARG(int) : \
	    (long)GETARG(int))
#define	UARG() \
	(flags&QUADINT ? GETARG(u_quad_t) : \
	    flags&LONGINT ? GETARG(u_long) : \
	    flags&PTRINT ? GETARG(intptr_t) : \
	    flags&SIZEINT ? GETARG(size_t) : \
	    flags&SHORTINT ? (u_long)(u_short)GETARG(int) : \
	    flags&CHARINT ? (u_long)(unsigned char)GETARG(int) : \
	    (u_long)GETARG(u_int))

	 /*
	  * Get * arguments, including the form *nn$.  Preserve the nextarg
	  * that the argument can be gotten once the type is determined.
	  */
#define GETASTER(val) \
	n2 = 0; \
	cp = fmt; \
	while (is_digit(*cp)) { \
		n2 = 10 * n2 + to_digit(*cp); \
		cp++; \
	} \
	if (*cp == '$') { \
		int hold = nextarg; \
		if (argtable == NULL) { \
			argtable = statargtable; \
			__find_arguments(fmt0, orgap, &argtable, &argtablesiz); \
		} \
		nextarg = n2; \
		val = GETARG(int); \
		nextarg = hold; \
		fmt = ++cp; \
	} else { \
		val = GETARG(int); \
	}

/*
 * Get the argument indexed by nextarg.   If the argument table is
 * built, use it to get the argument.  If its not, get the next
 * argument (and arguments must be gotten sequentially).
 */
#define GETARG(type) \
	(((argtable != NULL) ? (void)(ap = argtable[nextarg]) : (void)0), \
	 nextarg++, va_arg(ap, type))

	_SET_ORIENTATION(fp, -1);
	/* sorry, fprintf(read_only_file, "") returns EOF, not 0 */
	if (cantwrite(fp)) {
		errno = EBADF;
		return (EOF);
	}

	/* optimise fprintf(stderr) (and other unbuffered Unix files) */
	if ((fp->_flags & (__SNBF|__SWR|__SRW)) == (__SNBF|__SWR) &&
	    fp->_file >= 0)
		return (__sbprintf(fp, fmt0, ap));

	fmt = (char *)fmt0;
	argtable = NULL;
	nextarg = 1;
	va_copy(orgap, ap);
	uio.uio_iov = iovp = iov;
	uio.uio_resid = 0;
	uio.uio_iovcnt = 0;
	ret = 0;

	memset(&ps, 0, sizeof(ps));
	/*
	 * Scan the format for conversions ('%' character).
	 */
	for (;;) {
#ifdef __MirBSD__
		for (cp = fmt; (ch = *fmt) != '\0' && ch != '%'; ++fmt)
			;
#else
		cp = fmt;
		while ((n = mbrtowc(&wc, fmt, MB_CUR_MAX, &ps)) > 0) {
			fmt += n;
			if (wc == L'%') {
				fmt--;
				break;
			}
		}
#endif
		if ((m = fmt - cp) != 0) {
			PRINT(cp, m);
			ADDTORET(m);
		}
#ifdef __MirBSD__
		if (ch == '\0')
#else
		if (n <= 0)
#endif
			goto done;
		fmt++;		/* skip over '%' */

		flags = 0;
		dprec = 0;
		width = 0;
		prec = -1;
		sign = '\0';

 rflag:		ch = *fmt++;
 reswitch:	switch (ch) {
		case ' ':
			/*
			 * ''If the space and + flags both appear, the space
			 * flag will be ignored.''
			 *	-- ANSI X3J11
			 */
			if (!sign)
				sign = ' ';
			goto rflag;
		case '#':
			flags |= ALT;
			goto rflag;
		case '*':
			/*
			 * ''A negative field width argument is taken as a
			 * - flag followed by a positive field width.''
			 *	-- ANSI X3J11
			 * They don't exclude field widths read from args.
			 */
			GETASTER(width);
			if (width >= 0)
				goto rflag;
			width = -width;
			/* FALLTHROUGH */
		case '-':
			flags |= LADJUST;
			goto rflag;
		case '+':
			sign = '+';
			goto rflag;
		case '.':
			if ((ch = *fmt++) == '*') {
				GETASTER(n);
				prec = n < 0 ? -1 : n;
				goto rflag;
			}
			n = 0;
			while (is_digit(ch)) {
				n = 10 * n + to_digit(ch);
				ch = *fmt++;
			}
			if (ch == '$') {
				nextarg = n;
				if (argtable == NULL) {
					argtable = statargtable;
					__find_arguments(fmt0, orgap,
					    &argtable, &argtablesiz);
				}
				goto rflag;
			}
			prec = n < 0 ? -1 : n;
			goto reswitch;
		case '0':
			/*
			 * ''Note that 0 is taken as a flag, not as the
			 * beginning of a field width.''
			 *	-- ANSI X3J11
			 */
			flags |= ZEROPAD;
			goto rflag;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n = 0;
			do {
				n = 10 * n + to_digit(ch);
				ch = *fmt++;
			} while (is_digit(ch));
			if (ch == '$') {
				nextarg = n;
				if (argtable == NULL) {
					argtable = statargtable;
					__find_arguments(fmt0, orgap,
					    &argtable, &argtablesiz);
				}
				goto rflag;
			}
			width = n;
			goto reswitch;
#ifdef FLOATING_POINT
		case 'L':
			flags |= LONGDBL;
			goto rflag;
#endif
		case 'h':
			if (*fmt == 'h') {
				fmt++;
				flags |= CHARINT;
			} else
				flags |= SHORTINT;
			goto rflag;
		case 'j':
#if (INTMAX_MIN != INT64_MIN) || (INTMAX_MAX != INT64_MAX) || \
    (UINTMAX_MAX != UINT64_MAX)
#error This code assumes that intmax_t = int64_t, uintmax_t = uint64_t
#endif
			flags |= QUADINT;
			goto rflag;
		case 'l':
			if (*fmt == 'l') {
				fmt++;
				flags |= QUADINT;
			} else {
				flags |= LONGINT;
			}
			goto rflag;
		case 'q':
			flags |= QUADINT;
			goto rflag;
		case 't':
			flags |= PTRINT;
			goto rflag;
		case 'z':
			flags |= SIZEINT;
			goto rflag;
		case 'C':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'c':
			if (flags & LONGINT) {
				mbstate_t lcs = { 0, 0 };

				wc = GETARG(wint_t);
				size = wcrtomb(buf, wc, &lcs);
				if ((size_t)size == (size_t)-1) {
					buf[0] = 0xEF;
					buf[1] = 0xBF;
					buf[2] = 0xBD;
					size = 3;
				}
				(cp = buf)[size] = '\0';
				goto procstr;
			}
			*(cp = buf) = GETARG(int);
			size = 1;
			sign = '\0';
			break;
		case 'D':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'd':
		case 'i':
			_uquad = SARG();
			if ((quad_t)_uquad < 0) {
				_uquad = -_uquad;
				sign = '-';
			}
			base = DEC;
			goto number;
#ifdef FLOATING_POINT
		case 'e':
		case 'E':
		case 'f':
		case 'g':
		case 'G':
			if (prec == -1) {
				prec = DEFPREC;
			} else if ((ch == 'g' || ch == 'G') && prec == 0) {
				prec = 1;
			}

			if (flags & LONGDBL) {
				_double = (double) GETARG(long double);
			} else {
				_double = GETARG(double);
			}

			/* do this before tricky precision changes */
			if (isinf(_double)) {
				if (_double < 0)
					sign = '-';
				cp = "Inf";
				size = 3;
				break;
			}
			if (isnan(_double)) {
				cp = "NaN";
				size = 3;
				break;
			}

			flags |= FPT;
			cp = cvt(_double, prec, flags, &softsign,
				&expt, ch, &ndig);
			if (ch == 'g' || ch == 'G') {
				if (expt <= -4 || expt > prec)
					ch = (ch == 'g') ? 'e' : 'E';
				else
					ch = 'g';
			}
			if (ch <= 'e') {	/* 'e' or 'E' fmt */
				--expt;
				expsize = exponent(expstr, expt, ch);
				size = expsize + ndig;
				if (ndig > 1 || flags & ALT)
					++size;
			} else if (ch == 'f') {		/* f fmt */
				if (expt > 0) {
					size = expt;
					if (prec || flags & ALT)
						size += prec + 1;
				} else	/* "0.X" */
					size = prec + 2;
			} else if (expt >= ndig) {	/* fixed g fmt */
				size = expt;
				if (flags & ALT)
					++size;
			} else
				size = ndig + (expt > 0 ?
					1 : 2 - expt);

			if (softsign)
				sign = '-';
			break;
#endif /* FLOATING_POINT */
		case 'm':
			n = errno;
			strerror_r(origerrno, cp = buf, BUF);
			/* strerror_r(3) may return EINVAL or ERANGE, but
			 * these are of no meaning to vfprintf -> clean up
			 */
			errno = n;
			goto procstr;
		case 'n':
			if (flags & QUADINT)
				*GETARG(quad_t *) = ret;
			else if (flags & LONGINT)
				*GETARG(long *) = ret;
			else if (flags & SHORTINT)
				*GETARG(short *) = ret;
			else if (flags & CHARINT)
				*GETARG(signed char *) = ret;
			else if (flags & PTRINT)
				*GETARG(ptrdiff_t *) = ret;
			else if (flags & SIZEINT)
				*GETARG(ssize_t *) = ret;
			else
				*GETARG(int *) = ret;
			continue;	/* no output */
		case 'O':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'o':
			_uquad = UARG();
			base = OCT;
			goto nosign;
		case 'p':
			/*
			 * ''The argument shall be a pointer to void.  The
			 * value of the pointer is converted to a sequence
			 * of printable characters, in an implementation-
			 * defined manner.''
			 *	-- ANSI X3J11
			 */
			/* NOSTRICT */
			_uquad = (u_long)GETARG(void *);
			base = HEX;
			xdigs = mbsd_digits_hex;
			flags |= HEXPREFIX;
			ch = 'x';
			goto nosign;
		case 'S':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 's':
			if (flags & LONGINT)
				goto gotls;
			if ((cp = GETARG(char *)) == NULL)
				cp = "(null)";
			goto procstr;
 gotls:
			if ((wcp = GETARG(wchar_t *)) == NULL)
				wcp = L"(null)";
			if ((size = wcstombs(NULL, wcp, 0) + 1) == 0) {
				/* EILSEQ */
				fp->_flags |= __SERR;
				goto error;
			}
			/* this is awkward, some kind of malloc wannabe */
			if (mmapalcsz)
				munmap(mmapalloc, mmapalcsz);
			cp = mmapalloc = (char *)mmap(NULL, mmapalcsz = size,
			    PROT_WRITE|PROT_READ, MAP_ANON|MAP_PRIVATE, -1, 0);
			if (mmapalloc == MAP_FAILED) {
				mmapalcsz = 0;
				ret = EOF;
				goto error;
			}
			/* now copy over the wide string */
			wcstombs(cp, wcp, size);
 procstr:
			if (prec >= 0) {
				/*
				 * can't use strlen; can only look for the
				 * NUL in the first 'prec' characters, and
				 * strlen() will go further.
				 */
				char *p = memchr(cp, 0, prec);

				size = p ? (p - cp) : prec;
			} else {
				size_t len;

				if ((len = strlen(cp)) > INT_MAX) {
					errno = ENOMEM;
					ret = EOF;
					goto error;
				}
				size = (int)len;
			}
			if (flags & LONGINT) {
				/*
				 * no partial multibyte characters are to be
				 * written - we know we are only called with
				 * either cp=buf pointing to one mbchar plus
				 * NUL or by gotls: cp=mmapalloc pointing to
				 * a NUL-terminated multibyte string; we ba-
				 * sically check if the input byte AFTER the
				 * last byte to be printed is a continuation
				 * character and wind back until it isn't; a
				 * trick that can only work on already vali-
				 * dated NUL-terminated pure OPTU-8 strings.
				 */
#if !defined(__STDC_ISO_10646__) || (__STDC_ISO_10646__ != 200009L)
#error This code assumes OPTU-8 intrinsics from MirBSD
#endif
				while (size && ((cp[size] & 0xC0) == 0x80))
					--size;
			}
			sign = '\0';
			break;
		case 'U':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'u':
			_uquad = UARG();
			base = DEC;
			goto nosign;
		case 'X':
			xdigs = mbsd_digits_HEX;
			goto hex;
		case 'x':
			xdigs = mbsd_digits_hex;
 hex:			_uquad = UARG();
			base = HEX;
			/* leading 0x/X only if non-zero */
			if (flags & ALT && _uquad != 0)
				flags |= HEXPREFIX;

			/* unsigned conversions */
 nosign:		sign = '\0';
			/*
			 * ''... diouXx conversions ... if a precision is
			 * specified, the 0 flag will be ignored.''
			 *	-- ANSI X3J11
			 */
 number:		if ((dprec = prec) >= 0)
				flags &= ~ZEROPAD;

			/*
			 * ''The result of converting a zero value with an
			 * explicit precision of zero is no characters.''
			 *	-- ANSI X3J11
			 */
			cp = buf + BUF;
			if (_uquad != 0 || prec != 0) {
				/*
				 * Unsigned mod is hard, and unsigned mod
				 * by a constant is easier than that by
				 * a variable; hence this switch.
				 */
				switch (base) {
				case OCT:
					do {
						*--cp = to_char(_uquad & 7);
						_uquad >>= 3;
					} while (_uquad);
					/* handle octal leading 0 */
					if (flags & ALT && *cp != '0')
						*--cp = '0';
					break;

				case DEC:
					/* many numbers are 1 digit */
					while (_uquad >= 10) {
						*--cp = to_char(_uquad % 10);
						_uquad /= 10;
					}
					*--cp = to_char(_uquad);
					break;

				case HEX:
					do {
						*--cp = xdigs[_uquad & 15];
						_uquad >>= 4;
					} while (_uquad);
					break;

				default:
					cp = "bug in vfprintf: bad base";
					size = strlen(cp);
					goto skipsize;
				}
			}
			size = buf + BUF - cp;
		skipsize:
			break;
		default:	/* "%?" prints ?, unless ? is NUL */
			if (ch == '\0')
				goto done;
			/* pretend it was %c with argument ch */
			cp = buf;
			*cp = ch;
			size = 1;
			sign = '\0';
			break;
		}

		/*
		 * All reasonable formats wind up here.  At this point, 'cp'
		 * points to a string which (if not flags&LADJUST) should be
		 * padded out to 'width' places.  If flags&ZEROPAD, it should
		 * first be prefixed by any sign or other prefix; otherwise,
		 * it should be blank padded before the prefix is emitted.
		 * After any left-hand padding and prefixing, emit zeroes
		 * required by a decimal [diouxX] precision, then print the
		 * string proper, then emit zeroes required by any leftover
		 * floating precision; finally, if LADJUST, pad with blanks.
		 *
		 * Compute actual size, so we know how much to pad.
		 * size excludes decimal prec; realsz includes it.
		 */
		realsz = dprec > size ? dprec : size;
		if (sign)
			realsz++;
		else if (flags & HEXPREFIX)
			realsz+= 2;

		/* right-adjusting blank padding */
		if ((flags & (LADJUST|ZEROPAD)) == 0)
			PAD(width - realsz, blanks);

		/* prefix */
		if (sign) {
			PRINT(&sign, 1);
		} else if (flags & HEXPREFIX) {
			ox[0] = '0';
			ox[1] = ch;
			PRINT(ox, 2);
		}

		/* right-adjusting zero padding */
		if ((flags & (LADJUST|ZEROPAD)) == ZEROPAD)
			PAD(width - realsz, zeroes);

		/* leading zeroes from decimal precision */
		PAD(dprec - size, zeroes);

		/* the string or number proper */
#ifdef FLOATING_POINT
		if ((flags & FPT) == 0) {
			PRINT(cp, size);
		} else {	/* glue together f_p fragments */
			if (ch >= 'f') {	/* 'f' or 'g' */
				if (_double == 0) {
					/* kludge for __dtoa irregularity */
					PRINT("0", 1);
					if (expt < ndig || (flags & ALT) != 0) {
						PRINT(decimal_point, 1);
						PAD(ndig - 1, zeroes);
					}
				} else if (expt <= 0) {
					PRINT("0", 1);
					PRINT(decimal_point, 1);
					PAD(-expt, zeroes);
					PRINT(cp, ndig);
				} else if (expt >= ndig) {
					PRINT(cp, ndig);
					PAD(expt - ndig, zeroes);
					if (flags & ALT)
						PRINT(".", 1);
				} else {
					PRINT(cp, expt);
					cp += expt;
					PRINT(".", 1);
					PRINT(cp, ndig-expt);
				}
			} else {	/* 'e' or 'E' */
				if (ndig > 1 || flags & ALT) {
					ox[0] = *cp++;
					ox[1] = '.';
					PRINT(ox, 2);
					if (_double) {
						PRINT(cp, ndig-1);
					} else	/* 0.[0..] */
						/* __dtoa irregularity */
						PAD(ndig - 1, zeroes);
				} else	/* XeYYY */
					PRINT(cp, 1);
				PRINT(expstr, expsize);
			}
		}
#else
		PRINT(cp, size);
#endif
		/* left-adjusting padding (always blank) */
		if (flags & LADJUST)
			PAD(width - realsz, blanks);

		/* finally, adjust ret */
		ADDTORET(width > realsz ? width : realsz);

		FLUSH();	/* copy out the I/O vectors */
	}
 done:
	FLUSH();
 error:
	if (argtable != NULL && argtable != statargtable) {
		munmap(argtable, argtablesiz);
		argtable = NULL;
	}
	if (mmapalcsz)
		munmap(mmapalloc, mmapalcsz);
	return (__sferror(fp) ? EOF : ret);
	/* NOTREACHED */
}

/*
 * Type ids for argument type table.
 */
#define T_UNUSED	0
#define T_SHORT		1
#define T_U_SHORT	2
#define TP_SHORT	3
#define T_INT		4
#define T_U_INT		5
#define TP_INT		6
#define T_LONG		7
#define T_U_LONG	8
#define TP_LONG		9
#define T_QUAD		10
#define T_U_QUAD	11
#define TP_QUAD		12
#define T_DOUBLE	13
#define T_LONG_DOUBLE	14
#define TP_CHAR		15
#define TP_VOID		16
#define T_PTRINT	17
#define TP_PTRINT	18
#define T_SIZEINT	19
#define T_SSIZEINT	20
#define TP_SSIZEINT	21
#define T_WINTT		22
#define TP_WCHART	23
#define T_CHAR		24
#define T_U_CHAR	25
#define	TP_SCHAR	26
#define T_U_PTRINT	27

/*
 * Find all arguments when a positional parameter is encountered.  Returns a
 * table, indexed by argument number, of pointers to each arguments.  The
 * initial argument table should be an array of STATIC_ARG_TBL_SIZE entries.
 * It will be replaced with a mmap-ed one if it overflows (malloc cannot be
 * used since we are attempting to make snprintf thread safe, and alloca is
 * problematic since we have nested functions..)
 */
static void
__find_arguments(const char *fmt0, va_list ap, va_list **argtable,
    size_t *argtablesiz)
{
	char *fmt;	/* format string */
	int ch;	/* character from fmt */
	int n, n2;	/* handy integer (short term usage) */
	char *cp;	/* handy char pointer (short term usage) */
	int flags;	/* flags as above */
	unsigned char *typetable; /* table of types */
	unsigned char stattypetable[STATIC_ARG_TBL_SIZE];
	int tablesize;		/* current size of type table */
	int tablemax;		/* largest used index in table */
	int nextarg;		/* 1-based argument index */
	wchar_t wc;
	mbstate_t ps;

	/*
	 * Add an argument type to the table, expanding if necessary.
	 */
#define ADDTYPE(type) \
	((nextarg >= tablesize) ? \
		__grow_type_table(&typetable, &tablesize) : 0, \
	(nextarg > tablemax) ? tablemax = nextarg : 0, \
	typetable[nextarg++] = type)

#define	ADDSARG() \
	((flags&QUADINT) ? ADDTYPE(T_QUAD) : \
	    ((flags&LONGINT) ? ADDTYPE(T_LONG) : \
	    ((flags&CHARINT) ? ADDTYPE(T_CHAR) : \
		((flags&SHORTINT) ? ADDTYPE(T_SHORT) : ADDTYPE(T_INT)))))

#define	ADDUARG() \
	((flags&QUADINT) ? ADDTYPE(T_U_QUAD) : \
	    ((flags&LONGINT) ? ADDTYPE(T_U_LONG) : \
	    ((flags&CHARINT) ? ADDTYPE(T_U_CHAR) : \
		((flags&SHORTINT) ? ADDTYPE(T_U_SHORT) : ADDTYPE(T_U_INT)))))

	/*
	 * Add * arguments to the type array.
	 */
#define ADDASTER() \
	n2 = 0; \
	cp = fmt; \
	while (is_digit(*cp)) { \
		n2 = 10 * n2 + to_digit(*cp); \
		cp++; \
	} \
	if (*cp == '$') { \
		int hold = nextarg; \
		nextarg = n2; \
		ADDTYPE(T_INT); \
		nextarg = hold; \
		fmt = ++cp; \
	} else { \
		ADDTYPE(T_INT); \
	}
	fmt = (char *)fmt0;
	typetable = stattypetable;
	tablesize = STATIC_ARG_TBL_SIZE;
	tablemax = 0;
	nextarg = 1;
	memset(typetable, T_UNUSED, STATIC_ARG_TBL_SIZE);
	memset(&ps, 0, sizeof(ps));

	/*
	 * Scan the format for conversions ('%' character).
	 */
	for (;;) {
#ifdef __MirBSD__
		for (cp = fmt; (ch = *fmt) != '\0' && ch != '%'; ++fmt)
			;
		if (ch == '\0')
#else
		cp = fmt;
		while ((n = mbrtowc(&wc, fmt, MB_CUR_MAX, &ps)) > 0) {
			fmt += n;
			if (wc == L'%') {
				fmt--;
				break;
			}
		}
		if (n <= 0)
#endif
			goto done;
		fmt++;		/* skip over '%' */

		flags = 0;

 rflag:		ch = *fmt++;
 reswitch:	switch (ch) {
		case ' ':
		case '#':
			goto rflag;
		case '*':
			ADDASTER();
			goto rflag;
		case '-':
		case '+':
			goto rflag;
		case '.':
			if ((ch = *fmt++) == '*') {
				ADDASTER();
				goto rflag;
			}
			while (is_digit(ch)) {
				ch = *fmt++;
			}
			goto reswitch;
		case '0':
			goto rflag;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n = 0;
			do {
				n = 10 * n + to_digit(ch);
				ch = *fmt++;
			} while (is_digit(ch));
			if (ch == '$') {
				nextarg = n;
				goto rflag;
			}
			goto reswitch;
#ifdef FLOATING_POINT
		case 'L':
			flags |= LONGDBL;
			goto rflag;
#endif
		case 'h':
			if (*fmt == 'h') {
				fmt++;
				flags |= CHARINT;
			} else
				flags |= SHORTINT;
			goto rflag;
		case 'l':
			if (*fmt == 'l') {
				fmt++;
				flags |= QUADINT;
			} else {
				flags |= LONGINT;
			}
			goto rflag;
		case 'j':
		case 'q':
			flags |= QUADINT;
			goto rflag;
		case 't':
			flags |= PTRINT;
			goto rflag;
		case 'z':
			flags |= SIZEINT;
			goto rflag;
		case 'C':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'c':
			if (flags & LONGINT)
				ADDTYPE(T_WINTT);
			else
				ADDTYPE(T_INT);
			break;
		case 'D':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'd':
		case 'i':
			if (flags & QUADINT)
				ADDTYPE(T_QUAD);
			else if (flags & PTRINT)
				ADDTYPE(T_PTRINT);
			else if (flags & SIZEINT)
				ADDTYPE(T_SSIZEINT);
			else
				ADDSARG();
			break;
#ifdef FLOATING_POINT
		case 'e':
		case 'E':
		case 'f':
		case 'g':
		case 'G':
			if (flags & LONGDBL)
				ADDTYPE(T_LONG_DOUBLE);
			else
				ADDTYPE(T_DOUBLE);
			break;
#endif /* FLOATING_POINT */
		case 'n':
			if (flags & QUADINT)
				ADDTYPE(TP_QUAD);
			else if (flags & LONGINT)
				ADDTYPE(TP_LONG);
			else if (flags & SHORTINT)
				ADDTYPE(TP_SHORT);
			else if (flags & CHARINT)
				ADDTYPE(TP_SCHAR);
			else if (flags & PTRINT)
				ADDTYPE(TP_PTRINT);
			else if (flags & SIZEINT)
				ADDTYPE(TP_SSIZEINT);
			else
				ADDTYPE(TP_INT);
			continue;	/* no output */
		case 'O':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'o':
			if (flags & QUADINT)
				ADDTYPE(T_U_QUAD);
			else
				ADDUARG();
			break;
		case 'p':
			ADDTYPE(TP_VOID);
			break;
		case 'S':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 's':
			if (flags & LONGINT)
				ADDTYPE(TP_WCHART);
			else
				ADDTYPE(TP_CHAR);
			break;
		case 'U':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'u':
			if (flags & QUADINT)
				ADDTYPE(T_U_QUAD);
			else
				ADDUARG();
			break;
		case 'X':
		case 'x':
			if (flags & QUADINT)
				ADDTYPE(T_U_QUAD);
			else if (flags & PTRINT)
				ADDTYPE(T_U_PTRINT);
			else if (flags & SIZEINT)
				ADDTYPE(T_SIZEINT);
			else
				ADDUARG();
			break;
		default:	/* "%?" prints ?, unless ? is NUL */
			if (ch == '\0')
				goto done;
			break;
		}
	}
 done:
	/*
	 * Build the argument table.
	 */
	if (tablemax >= STATIC_ARG_TBL_SIZE) {
		*argtablesiz = sizeof (va_list) * (tablemax + 1);
		*argtable = (va_list *)mmap(NULL, *argtablesiz,
		    PROT_WRITE|PROT_READ, MAP_ANON|MAP_PRIVATE, -1, 0);
	}

#if 0
	/* XXX is this required? */
	(*argtable) [0] = NULL;
#endif
	for (n = 1; n <= tablemax; n++) {
		va_copy((*argtable)[n], ap);
		switch (typetable[n]) {
		case T_UNUSED:
			(void) va_arg(ap, int);
			break;
		case T_SHORT:
			(void) va_arg(ap, int);
			break;
		case T_U_SHORT:
			(void) va_arg(ap, int);
			break;
		case TP_SHORT:
			(void) va_arg(ap, short *);
			break;
		case T_INT:
			(void) va_arg(ap, int);
			break;
		case T_U_INT:
			(void) va_arg(ap, unsigned int);
			break;
		case TP_INT:
			(void) va_arg(ap, int *);
			break;
		case T_LONG:
			(void) va_arg(ap, long);
			break;
		case T_U_LONG:
			(void) va_arg(ap, unsigned long);
			break;
		case TP_LONG:
			(void) va_arg(ap, long *);
			break;
		case T_QUAD:
			(void) va_arg(ap, quad_t);
			break;
		case T_U_QUAD:
			(void) va_arg(ap, u_quad_t);
			break;
		case TP_QUAD:
			(void) va_arg(ap, quad_t *);
			break;
		case T_DOUBLE:
			(void) va_arg(ap, double);
			break;
		case T_LONG_DOUBLE:
			(void) va_arg(ap, long double);
			break;
		case TP_CHAR:
			(void) va_arg(ap, char *);
			break;
		case TP_VOID:
			(void) va_arg(ap, void *);
			break;
		case T_PTRINT:
			(void) va_arg(ap, ptrdiff_t);
			break;
		case TP_PTRINT:
			(void) va_arg(ap, ptrdiff_t *);
			break;
		case T_SIZEINT:
			(void) va_arg(ap, size_t);
			break;
		case T_SSIZEINT:
			(void) va_arg(ap, ssize_t);
			break;
		case TP_SSIZEINT:
			(void) va_arg(ap, ssize_t *);
			break;
		case T_WINTT:
			(void) va_arg(ap, wint_t);
			break;
		case TP_WCHART:
			(void) va_arg(ap, wchar_t *);
			break;
		case T_CHAR:
			(void) va_arg(ap, int);
			break;
		case T_U_CHAR:
			(void) va_arg(ap, int);
			break;
		case TP_SCHAR:
			(void) va_arg(ap, signed char *);
			break;
		case T_U_PTRINT:
			(void) va_arg(ap, intptr_t);
			break;
		}
	}

	if (typetable != NULL && typetable != stattypetable) {
		munmap(typetable, *argtablesiz);
		typetable = NULL;
	}
}

/*
 * Increase the size of the type table.
 */
static int
__grow_type_table(unsigned char **typetable, int *tablesize)
{
	unsigned char *oldtable = *typetable;
	int newsize = *tablesize * 2;

	if (*tablesize == STATIC_ARG_TBL_SIZE) {
		*typetable = (unsigned char *)mmap(NULL,
		    sizeof (unsigned char) * newsize, PROT_WRITE|PROT_READ,
		    MAP_ANON|MAP_PRIVATE, -1, 0);
		/* XXX unchecked */
		memmove(*typetable, oldtable, *tablesize);
	} else {
		unsigned char *new = (unsigned char *)mmap(NULL,
		    sizeof (unsigned char) * newsize, PROT_WRITE|PROT_READ,
		    MAP_ANON|MAP_PRIVATE, -1, 0);
		memmove(new, *typetable, *tablesize);
		munmap(*typetable, *tablesize);
		*typetable = new;
		/* XXX unchecked */
	}
	memset(*typetable + *tablesize, T_UNUSED, (newsize - *tablesize));

	*tablesize = newsize;
	return(0);
}


#ifdef FLOATING_POINT

extern char *__dtoa(double, int, int, int *, int *, char **);

static char *
cvt(double value, int ndigits, int flags, char *sign, int *decpt, int ch,
    int *length)
{
	int mode, dsgn;
	char *digits, *bp, *rve;

	if (ch == 'f') {
		mode = 3;		/* ndigits after the decimal point */
	} else {
		/* To obtain ndigits after the decimal point for the 'e'
		 * and 'E' formats, round to ndigits + 1 significant
		 * figures.
		 */
		if (ch == 'e' || ch == 'E') {
			ndigits++;
		}
		mode = 2;		/* ndigits significant digits */
	}

	if (value < 0) {
		value = -value;
		*sign = '-';
	} else
		*sign = '\000';
	digits = __dtoa(value, mode, ndigits, decpt, &dsgn, &rve);
	if ((ch != 'g' && ch != 'G') || flags & ALT) {	/* Print trailing zeros */
		bp = digits + ndigits;
		if (ch == 'f') {
			if (*digits == '0' && value)
				*decpt = -ndigits + 1;
			bp += *decpt;
		}
		if (value == 0)	/* kludge for __dtoa irregularity */
			rve = bp;
		while (rve < bp)
			*rve++ = '0';
	}
	*length = rve - digits;
	return (digits);
}

static int
exponent(char *p0, int exp, int fmtch)
{
	char *p, *t;
	char expbuf[MAXEXP];

	p = p0;
	*p++ = fmtch;
	if (exp < 0) {
		exp = -exp;
		*p++ = '-';
	}
	else
		*p++ = '+';
	t = expbuf + MAXEXP;
	if (exp > 9) {
		do {
			*--t = to_char(exp % 10);
		} while ((exp /= 10) > 9);
		*--t = to_char(exp);
		for (; t < expbuf + MAXEXP; *p++ = *t++);
	}
	else {
		*p++ = '0';
		*p++ = to_char(exp);
	}
	return (p - p0);
}
#endif /* FLOATING_POINT */
