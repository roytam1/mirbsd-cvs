/*
 * Copyright (c) 1991 The Regents of the University of California.
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
 */

#if 0
static char *rcsid = "$OpenBSD: multibyte.c,v 1.4 2003/06/02 20:18:38 millert Exp $";
#endif /* LIBC_SCCS and not lint */

#include <stdlib.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/multibyte.c,v 1.2 2005/11/21 20:40:39 tg Exp $");

/*
 * Stub multibyte character functions.
 * This cheezy implementation is fixed to the native single-byte
 * character set.
 */

int
__weak_mblen(s, n)
	const char *s;
	size_t n;
{
	if (s == NULL || *s == '\0')
		return 0;
	if (n == 0)
		return -1;
	return 1;
}

/*ARGSUSED*/
int
__weak_mbtowc(pwc, s, n)
	wchar_t *pwc;
	const char *s;
	size_t n;
{
	if (s == NULL)
		return 0;
	if (n == 0)
		return -1;
	if (pwc)
		*pwc = (wchar_t) *s;
	return (*s != '\0');
}

/*ARGSUSED*/
int
__weak_wctomb(char *s, wchar_t wchar)
{
	if (s == NULL)
		return 0;

	*s = (char) wchar;
	return 1;
}

/*ARGSUSED*/
size_t
__weak_mbstowcs(pwcs, s, n)
	wchar_t *pwcs;
	const char *s;
	size_t n;
{
	int count = 0;

	if (n != 0) {
		do {
			if ((*pwcs++ = (wchar_t) *s++) == 0)
				break;
			count++;
		} while (--n != 0);
	}
	
	return count;
}

/*ARGSUSED*/
size_t
__weak_wcstombs(s, pwcs, n)
	char *s;
	const wchar_t *pwcs;
	size_t n;
{
	int count = 0;

	if (n != 0) {
		do {
			if ((*s++ = (char) *pwcs++) == 0)
				break;
			count++;
		} while (--n != 0);
	}

	return count;
}

int
__weak_iswalnum(wint_t x)
{
	return isalnum(x);
}

int
__weak_iswalpha(wint_t x)
{
	return isalpha(x);
}

int
__weak_iswlower(wint_t x)
{
	return islower(x);
}

int
__weak_iswupper(wint_t x)
{
	return isupper(x);
}

wint_t
__weak_towlower(wint_t x)
{
	return tolower(x);
}

wint_t
__weak_towupper(wint_t x)
{
	return toupper(x);
}

__weak_alias(mblen, __weak_mblen);
__weak_alias(mbtowc, __weak_mbtowc);
__weak_alias(wctomb, __weak_wctomb);
__weak_alias(mbstowcs, __weak_mbstowcs);
__weak_alias(wcstombs, __weak_wcstombs);
__weak_alias(iswalnum, __weak_iswalnum);
__weak_alias(iswalpha, __weak_iswalpha);
__weak_alias(iswlower, __weak_iswlower);
__weak_alias(iswupper, __weak_iswupper);
__weak_alias(towlower, __weak_towlower);
__weak_alias(towupper, __weak_towupper);
