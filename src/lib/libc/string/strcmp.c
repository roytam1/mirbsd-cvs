/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

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
 * Implementation of strcmp(3), and of strcoll(3) for a system with 2
 * locales, specifically, 'C' and an UTF-8 locale. Collating informa-
 * tion for both is to go after the bit order.
 */

#if defined(_KERNEL) || defined(_STANDALONE)
#include <lib/libkern/libkern.h>
#else
#include <string.h>
#endif

__RCSID("$MirOS$");

#ifdef STRCOLL
#define strcmp strcoll
#endif

int
strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == L'\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)--s2);
}
