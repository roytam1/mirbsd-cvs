/* $MirOS: contrib/hosted/fwcf/adler.h,v 1.2 2006/09/19 11:30:24 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * The adler32 algorithm is
 * Copyright (C) 1995 Mark Adler
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
 * See also:
 *	contrib/hosted/fwcf/adler.h,v
 *	src/sys/arch/i386/stand/libz/adler32.S,v
 *	src/sys/lib/libsa/adler32s.c,v
 */

#ifndef ADLER_H
#define ADLER_H	"$MirOS: contrib/hosted/fwcf/adler.h,v 1.2 2006/09/19 11:30:24 tg Exp $"

#define ADLER_BASE 65521 /* largest prime smaller than 65536 */
#define ADLER_NMAX 5552	 /* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

/* declare everything needed by the adler32 routine */
#define ADLER_DECL		unsigned s1 = 1, s2 = 0, n

/* calculate the adler32 crc of the data pointed to
   by the 'buffer' argument, size expected in 'len'
   which is TRASHED; stores the result in s1 and s2 */
#define ADLER_CALC(buffer)	do {				\
		uint8_t *adler_buf = (uint8_t *)(buffer);	\
		while (len) {					\
			len -= (n = MIN(len, ADLER_NMAX));	\
			while (n--) {				\
				s1 += *adler_buf++;		\
				s2 += s1;			\
			}					\
			s1 %= ADLER_BASE;			\
			s2 %= ADLER_BASE;			\
		}						\
	} while (0)

#endif
