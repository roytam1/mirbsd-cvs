/* $MirOS: src/share/misc/licence.template,v 1.7 2006/04/09 22:08:49 tg Rel $ */

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
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Reinitialise the 31-bit PRNG but retain a little state information
 */

#include <sys/types.h>
#include <lib/libkern/libkern.h>

extern u_long _randseed;

void
srandom(u_long newseed)
{
	u_long t = _randseed;

	_randseed ^= newseed;
	while (_randseed & ~0x7FFFFFFF)
		_randseed = (_randseed >> 31) + (_randseed & 0x7FFFFFFF);

	t ^= (random() << 1) | (random() & 1);
	_randseed = newseed & 0x7FFFFFFF;

	while (t) {
		random();
		t >>= 1;
	}
}
