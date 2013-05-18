/* $MirOS: src/sys/lib/libsa/adler32s.c,v 1.1 2006/10/07 21:36:22 tg Exp $ */

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
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#ifdef _STANDALONE
#define zADDRND(x)	/* nothing */
#define zRCSID(x)	/* nothing, for space reasons */
#include <limits.h>
#else
#include <sys/param.h>
#ifdef _KERNEL
#include <sys/kernel.h>
#include <sys/limits.h>
#include <dev/rndvar.h>
#define zADDRND(x)	rnd_addpool_add((uint32_t)(x) ^ (uint32_t)time.tv_sec)
#define zRCSID(x)	/* nothing, for space reasons */
#else
#include <limits.h>
#include <stdlib.h>
#define zADDRND(x)	arc4random_push((int)(x))
#define zRCSID(x)	__RCSID(x);
#endif
#endif

zRCSID("$MirOS: src/sys/lib/libsa/adler32s.c,v 1.1 2006/10/07 21:36:22 tg Exp $")

unsigned long adler32(unsigned long, const unsigned char *, unsigned);

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
#define MINLBIT	16	/* min. number of bits required to represent BASE */

#ifndef MIN
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef NULL
#define NULL		((void *)0UL)
#endif

unsigned long
adler32(unsigned long s1, const unsigned char *buf, unsigned len)
{
	unsigned long s2;
	unsigned n;

	/* compile-time assertion: we must fit 32 bits into an unsigned long */
	switch (0) {
	case 0:
	case sizeof(unsigned long) * CHAR_BIT >= 32:
		;
	}

	/* compile-time assertion: we must fit MINLBIT bits into an unsigned */
	switch (0) {
	case 0:
	case sizeof(unsigned) * CHAR_BIT >= MINLBIT:
		;
	}

	if (buf == NULL)
		return (1UL);

	s2 = (s1 >> 16) & 0xFFFFUL;
	s1 &= 0xFFFFUL;

	while (len) {
		len -= (n = MIN(len, NMAX));
		while (n--) {
			s1 += *buf++;
			s2 += s1;
		}
		s1 %= BASE;
		s2 %= BASE;
	}

	s1 |= (s2 << 16);
	zADDRND(s1);		/* once-only evaluation of s1 not guaranteed */
	return (s1);
}
