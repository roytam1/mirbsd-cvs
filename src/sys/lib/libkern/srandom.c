/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2003
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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
	_randseed = (s1 & 0x01FFFFFF);
	s1 = random();
	_randseed = s1 ^ s2;
}
