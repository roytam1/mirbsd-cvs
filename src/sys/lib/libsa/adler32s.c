/* $MirOS: src/sys/lib/libsa/adler32s.c,v 1.2 2006/11/21 02:38:33 tg Exp $ */

/*-
 * Copyright (c) 2006
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

zRCSID("$MirOS: src/sys/lib/libsa/adler32s.c,v 1.2 2006/11/21 02:38:33 tg Exp $")

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
