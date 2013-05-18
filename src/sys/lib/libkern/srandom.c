/* $MirOS: src/sys/lib/libkern/srandom.c,v 1.8 2008/09/06 22:21:03 tg Exp $ */

/*-
 * Copyright (c) 2007, 2010
 *	Thorsten Glaser <tg@mirbsd.de>
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

#include <sys/systm.h>
#include <crypto/randimpl.h>

extern uint32_t _randseed;

void
srandom(u_long val)
{
	struct {
		u_long ov, nv;
	} x;

	x.ov = _randseed;
	x.nv = val;
	RNDEBUG(RD_SRANDOM, "srandom: %lu -> %lu\n", x.ov, x.nv);
	rnd_lopool_add(&x, sizeof(x));

	_randseed = val & 0x7FFFFFFF;
}
