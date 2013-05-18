/* $MirOS: src/lib/libc/time/tailibc.c,v 1.1 2007/02/07 20:43:24 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
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
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/taitime.h>

__RCSID("$MirOS: src/lib/libc/time/tailibc.c,v 1.1 2007/02/07 20:43:24 tg Exp $");

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
#endif
