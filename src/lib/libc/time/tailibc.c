/*-
 * Copyright (c) 2004, 2005, 2006, 2007, 2011
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

#include <sys/param.h>
#include <sys/time.h>
#define _IN_TAITIME_IMPLEMENTATION
#include <sys/taitime.h>
#include <stdlib.h>

__RCSID("$MirOS: src/lib/libc/time/tailibc.c,v 1.3+ 2011/11/20 04:57:13 tg Exp $");

#ifdef L_tai_time
tai64_t
tai_time(tai64_t *v)
{
	register int64_t t;
	struct timeval tv;

	/*
	 * We expect the kernel to count absolute seconds
	 * since the epoch 1970-01-01 00:00:00 UTC.
	 */
	gettimeofday(&tv, NULL);

	t = tv.tv_sec + __TAI64_BIAS;
	if (__predict_false(v != NULL))
		*v = t;

	return (t);
}
__warn_references(tai_time, "tai_time is deprecated; use the new mirtime API instead");
#endif

#ifdef L_taina_time
void
taina_time(tai64na_t *t)
{
	struct timespec tp;

	if (__predict_false(t == NULL))
		return;

	t->atto = 0;
	clock_gettime(CLOCK_REALTIME, &tp);
	t->secs = tp.tv_sec + __TAI64_BIAS;
	t->nano = (int32_t)tp.tv_nsec;
}
__warn_references(taina_time, "taina_time is deprecated; use the new mirtime API instead");
#endif

#ifdef L_djbtai
void
exporttai(uint8_t *dst, tai64na_t *src)
{
	struct {
		uint64_t secs;
		uint32_t nano;
		uint32_t atto;
	} *target;

	if (__predict_false((src == NULL) || (dst == NULL)))
		return;

	target = (void *)dst;
	target->secs = htobe64(__BOUNDINT0(0x7FFFFFFFFFFFFFFFLL, src->secs));
	target->nano = htobe32(__BOUNDINTU(999999999, src->nano));
	target->atto = htobe32(__BOUNDINTU(999999999, src->atto));
}
__warn_references(exporttai, "exporttai is deprecated; use the new mirtime API instead");

void
importtai(uint8_t *src, tai64na_t *dst)
{
	struct {
		uint64_t secs;
		uint32_t nano;
		uint32_t atto;
	} *source;

	if (__predict_false((src == NULL) || (dst == NULL)))
		return;

	source = (void *)src;
	dst->secs = betoh64(source->secs);
	dst->nano = __BOUNDINTU(999999999, betoh32(source->nano));
	dst->atto = __BOUNDINTU(999999999, betoh32(source->atto));
}
__warn_references(importtai, "importtai is deprecated; use the new mirtime API instead");
#endif

#ifdef L_tai_leaps

/*
 * this is to stay ABI compatible, i.e. avoid a libc major bump;
 * we don't care about _initialise_leaps, _leaps, _leaps_initialised
 * and _pushleap since they were internal symbols anyway, though
 */

tai64_t *
tai_leaps(void)
{
	static int initialised = 0;
	static tai64_t *tp, tnull = 0;

	if (!initialised) {
		size_t n = 0;
		const time_t *lp;

		lp = mirtime_getleaps();
		while (lp[n++])
			/* nothing */;
		if ((tp = calloc(n, sizeof(tai64_t))) == NULL) {
			/* yuk, cry ffs? */
			return (&tnull);
		}
		tp[--n] = 0;
		while (n--)
			tp[n] = timet2tai(lp[n]);
		initialised = 1;
	}
	return (tp);
}
__warn_references(tai_leaps, "tai_leaps is deprecated; use the new mirtime API instead");
#endif
