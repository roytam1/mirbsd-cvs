/*-
 * Copyright (c) 2009
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
 *-
 * This can be used to implement Bob Jenkins' one-at-a-time hash:
 *
 * uint32_t oaathash(const void *buf, size_t buflen = strlen(buf)) {
 *	return _oaat_final(_oaat_update(0, buf, buflen));
 * }
 *
 * Note that an initialisation value of 0x100 can count initial NULs,
 * but the original version uses 0 instead. (Anything is fine as long
 * as the lowest byte is 0x00 though.)
 */

#if 0	/* not yet */
#include <libckern.h>
#else
#include <sys/types.h>

uint32_t _oaat_update(register uint32_t, register const uint8_t *,
    register size_t) __attribute__((bounded (string, 2, 3)));
uint32_t _oaat_final(register uint32_t);
#endif

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

uint32_t
_oaat_update(register uint32_t h, register const uint8_t *s, register size_t n)
{
	while (n--) {
		h += *s++;
		h += h << 10;
		h ^= h >> 6;
	}

	return (h);
}

uint32_t
_oaat_final(register uint32_t h)
{
	h += h << 3;
	h ^= h >> 11;
	h += h << 15;

	return (h);
}
