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
 */

#ifndef ADLER_H
#define ADLER_H	"$MirOS$"

#define ADLER_BASE 65521 /* largest prime smaller than 65536 */
#define ADLER_NMAX 5552	 /* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define ADLER_START(buffer)					\
	{							\
		uint8_t *adler_buf = (uint8_t *)(buffer);	\
		unsigned s1 = 1, s2 = 0, n;

#define ADLER_RUN						\
		while (len) {					\
			len -= (n = MIN(len, ADLER_NMAX));	\
			while (n--) {				\
				s1 += *adler_buf++;		\
				s2 += s1;			\
			}					\
			s1 %= ADLER_BASE;			\
			s2 %= ADLER_BASE;			\
		}

#define ADLER_END						\
	}

#endif
