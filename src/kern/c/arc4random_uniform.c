/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 2008
 *	Damien Miller <djm@openbsd.org>
 * With simplifications by Jinmei Tatuya.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <libckern.h>
#include <limits.h>

__RCSID("$MirOS$");

/* u_int32_t in the original API, but we pray they're the same */
extern uint32_t arc4random(void);

/*
 * Calculate a uniformly distributed random number less than
 * upper_bound avoiding "modulo bias".
 *
 * Uniformity is achieved by generating new random numbers
 * until the one returned is outside the range
 * [0, 2^32 % upper_bound[. This guarantees the selected
 * random number will be inside the range
 * [2^32 % upper_bound, 2^32[ which maps back to
 * [0, upper_bound[ after reduction modulo upper_bound.
 */
uint32_t
arc4random_uniform(uint32_t upper_bound)
{
	uint32_t r, min;

	if (upper_bound < 2)
		return (0);

#if defined(ULONG_MAX) && (ULONG_MAX > 0xFFFFFFFFUL)
	min = 0x100000000UL % upper_bound;
#else
	/* calculate (2^32 % upper_bound) avoiding 64-bit math */
	if (upper_bound > 0x80000000U)
		/* 2^32 - upper_bound (only one "value area") */
		min = 1 + ~upper_bound;
	else
		/* ((2^32 - x) % x) == (2^32 % x) when x <= 2^31 */
		min = (0xFFFFFFFFU - upper_bound + 1) % upper_bound;
#endif

	/*
	 * This could theoretically loop forever but each retry has
	 * p > 0.5 (worst case, usually far better) of selecting a
	 * number inside the range we need, so it should rarely need
	 * to re-roll (at all).
	 */
	do {
		r = arc4random();
	} while (r < min);

	return (r % upper_bound);
}
