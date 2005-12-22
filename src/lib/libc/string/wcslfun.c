/* $MirOS: src/lib/libc/string/wcslfun.c,v 1.1 2005/09/21 20:47:20 tg Exp $ */
/* $OpenBSD: strlcpy.c,v 1.10 2005/08/08 08:05:37 espie Exp $ */
/* $OpenBSD: strlcat.c,v 1.13 2005/08/08 08:05:37 espie Exp $ */

/*-
 * Copyright (c) 2004, 2005 Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Thanks to Bodo Eggert for optimisation hints
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/string/wcslfun.c,v 1.1 2005/09/21 20:47:20 tg Exp $");

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns wcslen(src); if retval >= siz, truncation occurred.
 */
size_t
wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz)
{
	const wchar_t *s = src;

	if (!siz) goto traverse_src;

	/* Copy as many bytes as will fit */
	for (; --siz && (*dst++ = *s++); /* nothing */)
		;

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (!siz) {
		/* Save, since we've copied at max. (siz-1) characters */
		*dst = L'\0';	/* NUL-terminate dst */
traverse_src:
		while (*s++)
			;
	}

	return (s - src - 1);	/* count does not include NUL */
}

/*
 * Appends src to string dst of size siz (unlike wcsncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= wcslen(dst)).
 * Returns wcslen(src) + MIN(siz, wcslen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t
wcslcat(wchar_t *dst, const wchar_t *src, size_t siz)
{
	wchar_t *d = dst;
	size_t dl, n = siz;
	const size_t sl = wcslen(src);

	while (n-- && (*d++ != L'\0'))
		;
	if (!++n && (*d != L'\0'))
		return wcslen(src);

	dl = --d - dst;		/* original strlen(dst), max. siz-1 */
	n = siz - dl;
	dl += sl;

	if (!n--)
		return dl;

	if (n > sl)
		n = sl;		/* number of octets to copy */
	for (; n-- && (*d++ = *src++); /* nothing */)
		;
	*d = L'\0';		/* NUL-terminate dst */
	return dl;
}
