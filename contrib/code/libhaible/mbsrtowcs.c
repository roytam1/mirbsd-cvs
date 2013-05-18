/* $MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.9 2006/05/30 21:57:25 tg Exp $ */

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
#include <errno.h>

#include "mir18n.h"

__RCSID("$MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.9 2006/05/30 21:57:25 tg Exp $");

size_t
mbsrtowcs(wchar_t *__restrict__ pwcs, const char **__restrict__ s,
    size_t n, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal = { 0, 0 };
	const unsigned char *src = (const unsigned char *)(*s);
	wint_t c, w;
	size_t num, count = 0;

	if (ps == NULL)
		ps = &internal;

	if (!__locale_is_utf8) {
		while (((pwcs == NULL) ? 1 : n--) > 0) {
			c = *src++;
			if (c > MIR18N_SB_CVT) {
 ilseq:
				errno = EILSEQ;
				return ((size_t)(-1));
			}
			if (pwcs != NULL)
				pwcs[count] = (wchar_t)c;
			if (c == '\0') {
				src = NULL;
				break;
			}
			count++;
		}
	} else {
		while (((pwcs == NULL) ? 1 : n--) > 0) {
			const unsigned char *s2 = src;
			if (ps->count == 0) {
				c = *src;
				if (c < 0x80) {
					if (pwcs != NULL)
						pwcs[count] = (wchar_t)c;
					if (c == '\0') {
						src = NULL;
						break;
					}
					src++;
					count++;
					continue;
				} else if (c < 0xC2)
					goto ilseq;
				if (c < 0xE0) {
					w = (wchar_t)(c & 0x1F) << 6;
					num = 1;
				} else if (c < 0xF0) {
					w = (wchar_t)(c & 0x0F) << 12;
					num = 2;
				} else
					goto ilseq;
				src++;
			} else {
				w = ps->value << 6;
				num = ps->count;
			}
			for (;;) {
				c = *src++ ^ 0x80;
				if (!(c < 0x40))
					goto bad_input_backup;
				w |= (wchar_t)c << (6 * --num);
				if (num == 0)
					break;
				if (w < (1 << (5 * num + 6)))
					goto bad_input_backup;
			}
			if (pwcs != NULL) {
				pwcs[count] = w;
				ps->count = 0;
			}
			count++;
			continue;
 bad_input_backup:
			src = s2;
			goto ilseq;
		}
	}
	if (pwcs != NULL)
		*s = (const char *)src;
	return (count);
}
