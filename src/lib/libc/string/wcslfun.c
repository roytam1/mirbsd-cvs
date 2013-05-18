/* $MirOS: src/lib/libc/string/wcslfun.c,v 1.6 2006/11/08 23:22:07 tg Exp $ */
/* _MirOS: src/lib/libc/string/strlfun.c,v 1.10 2006/11/08 23:18:04 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 *-
 * The strlcat() code below has been written by Thorsten Glaser. Bodo
 * Eggert suggested optimising the strlcpy() code, originally written
 * by Todd C. Miller (see below), which was carried out by Th. Glaser
 * as well as writing wcslcat() and wcslcpy() equivalents.
 */

#include <sys/types.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/string/wcslfun.c,v 1.6 2006/11/08 23:22:07 tg Exp $");

#if !defined(HAVE_WCSLCAT) || (HAVE_WCSLCAT == 0)
/*
 * Appends src to wide string dst of size siz (unlike wcsncat, siz is the
 * full size of dst, not space left).  At most siz-1 wide characters
 * will be copied.  Always NUL terminates (unless siz <= wcslen(dst)).
 * Returns wcslen(src) + MIN(siz, wcslen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t
wcslcat(wchar_t *dst, const wchar_t *src, size_t dlen)
{
	size_t n = 0, slen;

	slen = wcslen(src);
	while (__predict_true(n + 1 < dlen && dst[n] != L'\0'))
		++n;
	if (__predict_false(dlen == 0 || dst[n] != L'\0'))
		return (dlen + slen);
	while (__predict_true((slen > 0) && (n < (dlen - 1)))) {
		dst[n++] = *src++;
		--slen;
	}
	dst[n] = L'\0';
	return (n + slen);
}
#endif

/* $OpenBSD: strlcpy.c,v 1.10 2005/08/08 08:05:37 espie Exp $ */

/*-
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

#if !defined(HAVE_WCSLCPY) || (HAVE_WCSLCPY == 0)
/*
 * Copy src to wide string dst of size siz.  At most siz-1 wide characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns wcslen(src); if retval >= siz, truncation occurred.
 */
size_t
wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz)
{
	const wchar_t *s = src;

	if (__predict_false(siz == 0))
		goto traverse_src;

	/* copy as many wide chars as will fit */
	while (--siz && (*dst++ = *s++))
		;

	/* not enough room in dst */
	if (__predict_false(siz == 0)) {
		/* safe to NUL-terminate dst since we copied <= siz-1 chars */
		*dst = L'\0';
 traverse_src:
		/* traverse rest of src */
		while (*s++)
			;
	}

	/* count doesn't include NUL */
	return (s - src - 1);
}
#endif
