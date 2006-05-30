/* $MirOS$ */
/*	$OpenBSD: wcstod.c,v 1.1 2005/07/01 08:59:27 espie Exp $	*/
/* $NetBSD: wcstod.c,v 1.4 2001/10/28 12:08:43 yamt Exp $ */

/*-
 * Copyright (c) 2006 MirOS Project,
 * Copyright (c)1999, 2000, 2001 Citrus Project,
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$Citrus: xpg4dl/FreeBSD/lib/libc/locale/wcstod.c,v 1.2 2001/09/27 16:23:57 yamt Exp $
 */

#include <sys/cdefs.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

long double
wcstold(const wchar_t *__restrict__ nptr, wchar_t **__restrict__ endptr)
{
	const wchar_t *src;
	size_t size;
	const wchar_t *start;

	/*
	 * check length of string and call strtod
	 */
	src = nptr;

	/* skip space first */
	while (iswspace(*src)) {
		src++;
	}

	/* get length of string */
	start = src;	
	if (wcschr(L"+-", *src))
		src++;
	size = wcsspn(src, L"0123456789");
	src += size;
	if (*src == L'.') {/* XXX use localeconv */
		src++;
		size = wcsspn(src, L"0123456789");
		src += size;
	}
	if (wcschr(L"Ee", *src)) {
		src++;
		if (wcschr(L"+-", *src))
			src++;
		size = wcsspn(src, L"0123456789");
		src += size;
	}
	size = src - start;

	/*
	 * convert to a char-string and pass it to strtod.
	 *
	 * since all mb chars used to represent a double-constant
	 * are in the portable character set, we can assume
	 * that they are 1-byte chars.
	 */
	if (size)
	{
		mbstate_t st;
		char *buf;
		char *end;
		const wchar_t *s;
		size_t size_converted;
		long double result;
		
		buf = malloc(size + 1);
		if (!buf) {
			/* error */
			errno = ENOMEM; /* XXX */
			return 0;
		}
			
		s = start;
		memset(&st, 0, sizeof(st));
		size_converted = wcsrtombs(buf, &s, size, &st);
		if (size != size_converted) {
			/* XXX should not happen */
			free(buf);
			errno = EILSEQ;
			return 0;
		}

		buf[size] = 0;
		result = strtod(buf, &end);

		free(buf);

		if (endptr)
			/* LINTED bad interface */
			*endptr = (wchar_t*)start + (end - buf);

		return result;
	}

	if (endptr)
		/* LINTED bad interface */
		*endptr = (wchar_t*)start;

	return 0;
}
#if 0
double	wcstod(const wchar_t *__restrict__, wchar_t **__restrict__);
float	wcstof(const wchar_t *__restrict__, wchar_t **__restrict__);
#endif
