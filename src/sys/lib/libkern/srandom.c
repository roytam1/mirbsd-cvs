/* $MirOS: src/sys/lib/libkern/srandom.c,v 1.4 2006/02/23 01:18:20 tg Exp $ */

/*-
 * Copyright (c) 2003, 2006
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
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Quick-Seed the pseudo-random number generator.
 * Here is no simple "let" operation, but an xor and rotation ops, so
 * nobody knows the exact state of the seed after this operation.
 */

#include <sys/types.h>

extern u_long _randseed;

void	srandom(u_long);
u_long	random(void);

void
srandom(u_long seed)
{
	u_long s1, s2;

	s1 = (_randseed & 0xFF) << 24;
	s2 = s1 + (_randseed & 0xFFFFFF) + (seed & 0x0F);
	s1 = s2 ^ (seed & 0x000FFFF0);
	seed >>= 20;
	while (seed) {
		random();
		if (seed & 1)
			random();
		seed >>= 1;
	}
	s2 = (s1 & 0x7F) << 24;
	s1 = (s1 & 0xFFFFFF80) >> 7;
	_randseed ^= (s1 & 0x01FFFFFF);
	random();
	_randseed = (_randseed ^ s2) & 0x7FFFFFFF;
}
