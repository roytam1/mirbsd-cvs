/* $MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.14 2006/05/30 23:06:34 tg Exp $ */

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
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <errno.h>
#include <wchar.h>

#include "mir18n.h"

__RCSID("$MirOS: contrib/code/libhaible/mbsrtowcs.c,v 1.14 2006/05/30 23:06:34 tg Exp $");

size_t
wcsrtombs(char *__restrict__ dst, const wchar_t **__restrict__ src,
    size_t len, mbstate_t *__restrict__ ps)
{
	static mbstate_t internal_mbstate = { 0, 0 };
	const wchar_t *s = *src;
	unsigned char *d = (unsigned char *)dst;
	size_t numb = 0;
	wint_t w;

	if (__predict_false(ps == NULL))
		ps = &internal_mbstate;

	/* first process any hanging bytes */
	while (__locale_is_utf8 && __predict_false(ps->count)) {
		if (d != NULL) {
			if (len-- == 0)
				return (numb);
			d[numb] = ((ps->value >> (6 * --ps->count)) & 0x3F)
			    | 0x80;
		}
		++numb;
	}

	/* now process the string */
 loop:
	w = *s++;
	if (!__locale_is_utf8 || (w < 0x80)) {
		if (!__locale_is_utf8 && __predict_false(w > MIR18N_SB_CVT)) {
 ilseq:
			errno = EILSEQ;
			return ((size_t)(-1));
		}
		if (d != NULL) {
			if (len-- == 0) {
				*src = --s;
				return (numb);
			}
			d[numb] = w;
		}
		if (w == 0) {
			*src = NULL;
			return (numb);
		}
	} else if (w < 0x0800) {
		ps->count = 1;
		ps->value = w;
		if (d != NULL) {
			if (len-- == 0) {
				*src = --s;
				return (numb);
			}
			d[numb] = (w >> 6) | 0xC0;
		}
	} else if (__predict_false(w > MIR18N_MB_MAX)) {
		goto ilseq;
	} else {
		ps->count = 2;
		ps->value = w;
		if (d != NULL) {
			if (len-- == 0) {
				*src = --s;
				return (numb);
			}
			d[numb] = (w >> 12) | 0xE0;
		}
	}
	++numb;

	while (__predict_false(ps->count)) {
		if (d != NULL) {
			if (len-- == 0) {
				*src = s;
				return (numb);
			}
			d[numb] = ((w >> (6 * --ps->count)) & 0x3F) | 0x80;
		}
		++numb;
	}

	goto loop;
}
