/* $MirOS: src/lib/libc/string/strcasecmp.c,v 1.3 2006/11/21 00:22:30 tg Exp $ */

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
 */

#include <wctype.h>

__RCSID("$MirOS: src/lib/libc/string/strcasecmp.c,v 1.3 2006/11/21 00:22:30 tg Exp $");

int
wcsncasecmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
	while (n--) {
		if (towlower(*s1) != towlower(*s2))
			return (towlower(*s1) - towlower(*s2));
		if (*s1++ == L'\0')
			break;
		s2++;
	}
	return (0);
}
