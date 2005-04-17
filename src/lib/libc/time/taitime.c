/* $MirOS: src/lib/libc/time/taitime.c,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <sys/param.h>
#include <stdint.h>
#include "private.h"
#include "tzfile.h"

__RCSID("$MirOS: src/lib/libc/time/taitime.c,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $");

static __inline tai64_t *_tai_leaps(void);


tai64_t
tai_time(tai64_t *v)
{
	struct timeval tv;
	register int64_t t = __TAI64_BIAS;

	/*
	 * We expect the kernel to count absolute seconds
	 * since the epoch 1970-01-01 00:00:00 UTC.
	 */
	gettimeofday(&tv, NULL);

	t += tv.tv_sec;
	if (__predict_false(v != NULL))
		*v = t;

	return t;
}

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


void
exporttai(u_int8_t *dst, tai64na_t *src)
{
	struct {
		u_int64_t secs;
		u_int32_t nano;
		u_int32_t atto;
	}     *target = (void *)dst;

	if (__predict_false((src == NULL) || (dst == NULL)))
		return;

	target->secs = htobe64(__BOUNDINT0(0x7FFFFFFFFFFFFFFFLL, src->secs));
	target->nano = htobe32(__BOUNDINTU(999999999, src->nano));
	target->atto = htobe32(__BOUNDINTU(999999999, src->atto));
}

void
importtai(u_int8_t *src, tai64na_t *dst)
{
	struct {
		u_int64_t secs;
		u_int32_t nano;
		u_int32_t atto;
	}     *source = (void *)src;

	if (__predict_false((src == NULL) || (dst == NULL)))
		return;

	dst->secs = betoh64(source->secs);
	dst->nano = __BOUNDINTU(999999999, betoh32(source->nano));
	dst->atto = __BOUNDINTU(999999999, betoh32(source->atto));
}


tai64_t
utc2tai(int64_t u)
{
	tai64_t t = u + __TAI64_BIAS;
	tai64_t *s = _tai_leaps();

	if (__predict_false(u < 0))
		return t;

	while (__predict_true((*s) && (t >= *s))) {
		++t;
		++s;
	}
	return t;
}

int64_t
tai2utc(tai64_t t)
{
	int64_t u = t - __TAI64_BIAS;
	tai64_t *s = _tai_leaps();

	if (__predict_true(u > 0))
		while (__predict_true((*s) && (t >= *s))) {
			--u;
			++s;
		}

	return u;
}


/* private interface */
tai64_t _leaps[TZ_MAX_LEAPS + 1] = {0};
int _leaps_initialised = 0;

/* private interface */
void
_pushleap(time_t leap)
{
	tai64_t *t = _leaps;
	tai64_t i = timet2tai(leap);

	while (__predict_true(*t))
		++t;
	*t++ = i;
	*t = 0;
}

/* private interface */
static __inline tai64_t *
_tai_leaps(void)
{
	extern void _initialise_leaps(void);

	if (__predict_false(!_leaps_initialised)) {
		_leaps_initialised = 1;
		_initialise_leaps();
	}
	return _leaps;
}

tai64_t *
tai_leaps(void)
{
	return _tai_leaps();
}

int
tai_isleap(tai64_t x)
{
	tai64_t *t;

	t = _tai_leaps();
	while (__predict_true(*t))
		if (__predict_false((*t) == x))
			return 1;
		else if (__predict_false((*t) > x))
			return 0;
		else
			++t;
	return 0;
}

/* normally a macro */
#ifndef timet2tai
tai64_t
timet2tai(time_t x)
{
	return (((u_int64_t)x < 0x4000000000000000ULL)
	    ? ((tai64_t)((u_int64_t)x + __TAI64_BIAS))
	    : (((u_int64_t)x < 0x8000000000000000ULL)
	    ? ((tai64_t)0x7FFFFFFFFFFFFFFFULL)
	    : (((u_int64_t)x < 0xC000000000000000ULL)
	    ? ((tai64_t)0ULL)
	    : ((tai64_t)((u_int64_t)x + __TAI64_BIAS)))));
}
#endif

/* normally a macro */
#ifndef tai2timet
time_t
tai2timet(tai64_t x)
{
	return (((u_int64_t)x & 0x8000000000000000ULL)
	    ? 0
	    : ((u_int64_t)x - __TAI64_BIAS));
}
#endif

tai64_t
mjd2tai(mjd_t m)
{
	int64_t x = (m.mjd - 40587LL) * 86400LL;
	tai64_t t;

	x += (m.sec > 86399) ? 86399 : m.sec;
	t = utc2tai(x);
	if (m.sec > 86399)
		++t;

	return t;
}

mjd_t
tai2mjd(tai64_t tai)
{
	int64_t x = tai2utc(tai);
	mjd_t m;

	m.sec = (int32_t)(x % 86400LL);
	m.mjd = (x / 86400LL) + 40587LL;

	while (__predict_false(m.sec < 0)) {
		m.sec += 86400;
		--m.mjd;
	}

	if (__predict_false(tai_isleap(tai)))
		++m.sec;

	return m;
}

/*
 * For more information on DJB products, such as libtai,
 * please go to http://cr.yp.to/
 */

/* from caldate_frommjd libtai-0.60 */
/* hacked up for time_t-64 support */

struct tm
mjd2tm(mjd_t m)
{
	time_t year;
	int month, day, yday, wday, sec, leap;
	struct tm res;

	memset(&res, 0, sizeof(res));

	year = m.mjd;
	sec = m.sec;

	while (sec < 0) {
		sec += 86400;
		--year;
	}

	while (sec > 86400) {
		sec -= 86400;
		++year;
	}

	leap = (sec == 86400);
	if (__predict_false(leap))
		--sec;

	day = (int32_t)(year % 146097LL) + 678881;
	year /= 146097LL;
	while (__predict_false(day >= 146097)) {
		day -= 146097;
		++year;
	}

	/* year * 146097 + day - 678881 is MJD; 0 <= day < 146097 */
	/* 2000-03-01, MJD 51604, is year 5, day 0 */

	wday = (day + 3) % 7;

	year *= 4;
	if (__predict_false(day == 146096)) {
		year += 3;
		day = 36524;
	} else {
		year += day / 36524LL;
		day %= 36524;
	}
	year *= 25;
	year += day / 1461;
	day %= 1461;
	year *= 4;

	yday = (day < 306);
	if (__predict_false(day == 1460)) {
		year += 3;
		day = 365;
	} else {
		year += day / 365;
		day %= 365;
	}
	yday += day;

	day *= 10;
	month = (day + 5) / 306;
	day = (day + 5) % 306;
	day /= 10;
	if (__predict_false(month >= 10)) {
		yday -= 306;
		++year;
		month -= 10;
	} else {
		yday += 59;
		month += 2;
	}
	if (__predict_false(year < 1))
		--year;

	res.tm_sec = (sec % 60);
	if (__predict_false(leap))
		++res.tm_sec;
	sec /= 60;
	res.tm_min = (sec % 60);
	res.tm_hour = (sec / 60);
	res.tm_mday = day + 1;
	res.tm_mon = month;
	res.tm_year = year - 1900;
	res.tm_wday = wday;
	res.tm_yday = yday;

	return res;
}

/* from caldate_mjd libtai-0.60 */
/* hacked up for time_t-64 support */

mjd_t
tm2mjd(struct tm tm)
{
	static unsigned long times365[4] = {
		0, 365, 730, 1095
	};
	static unsigned long times36524[4] = {
		0, 36524UL, 73048UL, 109572UL
	};
	static unsigned long montab[12] = {
		0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337
	};
	/* month length after february is (306 * m + 5) / 10 */

	time_t d = tm.tm_year + 1900LL;
	int m = tm.tm_mon;
	int y;
	long sec;
	mjd_t res;

	if (__predict_false(d < 0))
		++d;
	y = (int)(d % 400LL);
	d = 146097LL * (d / 400) + tm.tm_mday - 678882LL;
	sec = tm.tm_sec - tm.tm_gmtoff + 60 * (tm.tm_min + 60 * tm.tm_hour);

	while (__predict_false(sec < 0L)) {
		sec += 86400L;
		--d;
	}
	while (__predict_false(sec > 86400L)) {
		sec -= 86400L;
		++d;
	}

	if (m >= 2) {
		m -= 2;
	} else {
		m += 10;
		--y;
	}

	y += (m / 12);
	m %= 12;
	if (__predict_false(m < 0)) {
		m += 12;
		--y;
	}
	d += montab[m];

	d += 146097LL * (y / 400LL);
	y %= 400;
	while (__predict_false(y < 0)) {
		y += 400;
		d -= 146097LL;
	}

	d += times365[y & 3];
	y /= 4;

	d += 1461LL * (y % 25);
	y /= 25;

	d += times36524[y & 3];

	res.mjd = d;
	res.sec = (int32_t)sec;

	return res;
}
