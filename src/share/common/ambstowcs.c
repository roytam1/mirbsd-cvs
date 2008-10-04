/*-
 * Copyright (c) 2008
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

__RCSID("$MirOS: src/share/common/ambstowcs.c,v 1.1 2007/07/16 15:12:02 tg Exp $");

wchar_t *
ambstowcs(const char *s)
{
	wchar_t *ws;
	size_t n;

	if ((ws = calloc((n = mbstowcs(NULL, s, 0) + 1),
	    sizeof (wchar_t))) == NULL)
		err(1, "out of memory allocating %zu wide chars", n);
	mbstowcs(ws, s, n);
	return (ws);
}
