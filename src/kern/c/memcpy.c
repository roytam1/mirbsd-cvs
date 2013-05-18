/*-
 * Copyright (c) 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
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

#include <libckern.h>

__RCSID("$MirOS: src/kern/c/memcpy.c,v 1.2 2008/12/27 21:29:30 tg Exp $");

#ifdef L_mempcpy
#define memmove mempcpy
#endif

void *
memmove(void *dst, const void *src, size_t len)
{
	const uint8_t *s = src;
	uint8_t *d = dst;
#ifdef L_mempcpy
	uint8_t * const rv = dst + len;
#endif

	if (len) {
		if (src < dst) {
			s += len;
			d += len;
			while (len--)
				*--d = *--s;
		} else
			while (len--)
				*d++ = *s++;
	}
#ifdef L_mempcpy
	return (rv);
#else
	return (dst);
#endif
}

#ifndef L_mempcpy
#ifndef SMALL
void
bcopy(const void *src, void *dst, size_t len)
{
	memmove(dst, src, len);
}
#endif

#ifdef lint
int
memcpy(void *dst, const void *src, size_t len)
{
	return (memmove(dst, src, len));
}
#else
__strong_alias(memcpy, memmove);
#endif
#endif
