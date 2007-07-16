/*-
 * Copyright (c) 2007
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

#include <err.h>
#include <wchar.h>
#include "ambstowcs.h"

__RCSID("$MirOS$");

wchar_t *
ambstowcs(const char *s)
{
	wchar_t *ws = NULL;
	size_t n = 0, p = 0, ilen, b;

	ilen = strlen(s);

 ambstowcs_loop:
	if (p >= n && (ws = realloc(ws,
	    (n = (n ? n << 1 : 32)) * sizeof (wchar_t))) == NULL)
		err(1, "out of memory allocating %zu wide chars", n);
	if (ilen == 0) {
		ws[p] = L'\0';
		return (ws);
	} else if ((b = mbtowc(ws + p, s, ilen)) == (size_t)-1) {
		ws[p] = 0xFFFD;
		++s;
		--ilen;
	} else {
		s += b;
		ilen -= b;
	}
	++p;
	goto ambstowcs_loop;
}
