/* $MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.3 2006/05/30 21:36:44 tg Exp $ */

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

__RCSID("$MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.3 2006/05/30 21:36:44 tg Exp $");

size_t
mbsrtowcs(wchar_t *__restrict__ dest, const char **__restrict__ srcp,
    size_t len, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal;
	const unsigned char *src;
	size_t cnt = 0, count;
	unsigned char c;
	wchar_t wc;

	if (ps == NULL)
		ps = &internal;

	src = *srcp;
	if (!__locale_is_utf8) {
		while (((dest == NULL) ? 1 : len--) > 0) {
			c = *src++;
			if (dest != NULL)
				dest[cnt] = (wchar_t)c;
			if (c == '\0') {
				src = NULL;
				break;
			}
			cnt++;
		}
		*srcp = src;
		return (cnt);
	}
	if (dest != NULL) {
		while (len-- > 0) {
			const unsigned char *s2 = src;
			if (ps->count == 0) {
				c = *src;
				if (c < 0x80) {
					dest[cnt] = (wchar_t)c;
					if (c == '\0') {
						src = NULL;
						break;
					}
					src++;
					cnt++;
					continue;
				} else if (c < 0xC2)
					goto bad_input;
				if (c < 0xE0) {
					wc = (wchar_t)(c & 0x1F) << 6;
					count = 1;
				} else if (c < 0xF0) {
					wc = (wchar_t)(c & 0x0F) << 12;
					count = 2;
				} else
					goto bad_input;
				src++;
			} else {
				wc = ps->value << 6;
				count = ps->count;
			}
			for (;;) {
				c = *src++ ^ 0x80;
				if (!(c < 0x40))
					goto bad_input_backup;
				wc |= (wchar_t)c << (6 * --count);
				if (count == 0)
					break;
				if (wc < (1 << (5 * count + 6)))
					goto bad_input_backup;
			}
			dest[cnt] = wc;
			ps->count = 0;
			cnt++;
			continue;
 bad_input_backup:
			src = s2;
			goto bad_input;
		}
	} else {
		/* ignore dest and len */
		while (1) {
			const unsigned char *s2 = src;
			if (ps->count == 0) {
				c = *src;
				if (c < 0x80) {
					if (c == '\0') {
						src = NULL;
						break;
					}
					src++;
					cnt++;
					continue;
				} else if (c < 0xC2)
					goto bad_input;
				if (c < 0xE0) {
					wc = (wchar_t)(c & 0x1F) << 6;
					count = 1;
				} else if (c < 0xF0) {
					wc = (wchar_t)(c & 0x0F) << 12;
					count = 2;
				} else
					goto bad_input;
				src++;
			} else {
				wc = ps->value << 6;
				count = ps->count;
			}
			for (;;) {
				c = *src++ ^ 0x80;
				if (!(c < 0x40))
					goto bad_input_backup2;
				wc |= (wchar_t)c << (6 * --count);
				if (count == 0)
					break;
				if (wc < (1 << (5 * count + 6)))
					goto bad_input_backup2;
			}
			ps->count = 0;
			cnt++;
			continue;
 bad_input_backup2:
			src = s2;
			goto bad_input;
		}
	}
	*srcp = src;
	return (cnt);
 bad_input:
	*srcp = src;
	errno = EILSEQ;
	return ((size_t)(-1));
}
