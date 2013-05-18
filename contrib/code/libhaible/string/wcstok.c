/* $MirOS$ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Based upon code written by Bruno Haible for GNU libutf8:
 * Copyright (c) 1999, 2000, 2001
 *	Free Software Foundation, Inc.
 *
 * This work is licenced under the terms of the GNU Library General
 * Public License, Version 2, as in /usr/share/doc/legal/COPYING.LIB-2
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <wchar.h>

__RCSID("$MirOS$");

wchar_t	*wcstok(wchar_t *__restrict__ wcs, const wchar_t *__restrict__ delim,
    wchar_t **__restrict__ ptr)
{
	if (wcs == NULL) {
		wcs = *ptr;
		/* reminder that end of token sequence has been reached */
		if (wcs == NULL)
			return (NULL);
	}
	/* skip leading delimiters */
	wcs += wcsspn(wcs, delim);
	/* found a token? */
	if (*wcs == L'\0') {
		*ptr = NULL;
		return (NULL);
	}
	/* move past the token */
	{
		wchar_t *token_end = wcspbrk(wcs, delim);
		if (token_end) {
			/* NUL-terminate the token */
			*token_end = L'\0';
			*ptr = token_end + 1;
		} else
			*ptr = NULL;
	}
	return (wcs);
}
