/*-
 * Copyright (c) 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 * The adler32 algorithm is
 * Copyright (C) 1995 Mark Adler
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <sys/param.h>
#include <adler32.h>
#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/hash/suma.c,v 1.2 2007/05/07 15:55:27 tg Exp $");

void
ADLER32Init(ADLER32_CTX *ctx)
{
	if (ctx != NULL)
		*ctx = 1;
}

/*-
 * See also:
 *	contrib/hosted/fwcf/adler.h
 *	src/lib/libc/hash/adh32.c
 *	src/kern/z/adler32s.c
 *	src/kern/z/adler32_i386.S
 */
void
ADLER32Update(ADLER32_CTX *ctx, const uint8_t *buf, size_t len)
{
	uint32_t s1, s2, n;

	if (ctx == NULL)
		return;

	s1 = (s2 = *ctx) & 0xFFFF;;
	s2 >>= 16;

#define ADLER_BASE 65521 /* largest prime smaller than 65536 */
#define ADLER_NMAX 5552	 /* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
	while (len) {
		len -= (n = MIN(len, ADLER_NMAX));
		while (n--) {
			s1 += *buf++;
			s2 += s1;
		}
		s1 %= ADLER_BASE;
		s2 %= ADLER_BASE;
	}

	*ctx = s1 | (s2 << 16);
}

void
ADLER32Final(uint8_t *dst, ADLER32_CTX *ctx)
{
	if (dst)
		*((uint32_t *)dst) = htobe32(*ctx);
	*ctx = 0;
}
