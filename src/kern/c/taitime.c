/* $MirOS: src/kern/c/taitime.c,v 1.2 2007/02/07 21:46:44 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2006, 2007, 2011
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Based upon code placed into the public domain by
 *	Dan J. Bernstein <djb@cr.yp.to>
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

#include <sys/types.h>
#include <sys/taitime.h>

__RCSID("$MirOS: src/kern/c/taitime.c,v 1.2 2007/02/07 21:46:44 tg Exp $");

#ifdef __TAI_CAN_BE_64BIT
#define TU(x)	((uint64_t)(x))
#else
#define TU(x)	(x)
#endif

#ifdef L_tai_isleap
int
tai_isleap(tai64_t x)
{
	tai64_t *t;

	t = tai_leaps();
	while (__predict_true(*t))
		if (__predict_false((*t) == x))
			return (1);
		else if (__predict_false(TU(*t) > TU(x)))
			return (0);
		else
			++t;
	return (0);
}
#endif

#ifdef L_timet2tai
#undef timet2tai
tai64_t
timet2tai(time_t x)
{
#ifdef __TAI_CAN_BE_64BIT
	return ((tai64_t)((time_t)x + __TAI64_BIAS));
#else
	return (((uint64_t)x < 0x4000000000000000ULL)
	    ? ((tai64_t)((uint64_t)x + __TAI64_BIAS))
	    : (((uint64_t)x < 0x8000000000000000ULL)
	    ? ((tai64_t)0x7FFFFFFFFFFFFFFFULL)
	    : (((uint64_t)x < 0xC000000000000000ULL)
	    ? ((tai64_t)0ULL)
	    : ((tai64_t)((uint64_t)x + __TAI64_BIAS)))));
#endif
}
#endif

#ifdef L_tai2timet
#undef tai2timet
time_t
tai2timet(tai64_t x)
{
#ifdef __TAI_CAN_BE_64BIT
	return ((time_t)((tai64_t)x - __TAI64_BIAS));
#else
	return (((uint64_t)x & 0x8000000000000000ULL) ? 0 :
	    ((uint64_t)x - __TAI64_BIAS));
#endif
}
#endif

#ifdef L_utc2tai
tai64_t
utc2tai(int64_t u)
{
	tai64_t t, *s;

	t = u + __TAI64_BIAS;
	if (__predict_true(u > 0)) {
		s = tai_leaps();
		while (__predict_true((*s) && (TU(t) >= TU(*s)))) {
			++t;
			++s;
		}
	}
	return (t);
}
#endif

#ifdef L_tai2utc
int64_t
tai2utc(tai64_t t)
{
	int64_t u;
	tai64_t *s;

	u = t - __TAI64_BIAS;
	if (__predict_true(u > 0)) {
		s = tai_leaps();
		while (__predict_true((*s) && (TU(t) >= TU(*s)))) {
			--u;
			++s;
		}
	}
	return (u);
}
#endif

#ifdef L_mjd2tai
tai64_t
mjd2tai(mjd_t m)
{
	tai64_t t;

	t = utc2tai((m.mjd - 40587LL) * 86400LL +
	    ((m.sec > 86399) ? 86399 : m.sec));
	if (m.sec > 86399)
		++t;
	return (t);
}
#endif

#ifdef L_tai2mjd
mjd_t
tai2mjd(tai64_t tai)
{
	int64_t x;
	mjd_t m;

	x = tai2utc(tai);
	m.sec = (int32_t)(x % 86400LL);
	m.mjd = (x / 86400LL) + 40587LL;

	while (__predict_false(m.sec < 0)) {
		m.sec += 86400;
		--m.mjd;
	}

	if (__predict_false(tai_isleap(tai)))
		++m.sec;

	return (m);
}
#endif

/*
 * For more information on DJB products, such as libtai,
 * please go to http://cr.yp.to/
 */

#ifdef L_mjd2tm
/* from caldate_frommjd libtai-0.60 */
/* hacked up for time_t-64 support */

struct tm
mjd2tm(mjd_t m)
{
	time_t year;
	int month, day, yday, wday, sec, leap;
	struct tm res;

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

	if (__predict_false(leap = ((sec == 86400) ? 1 : 0)))
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

	res.tm_sec = (sec % 60) + leap;
	sec /= 60;
	res.tm_min = (sec % 60);
	res.tm_hour = (sec / 60);
	res.tm_mday = day + 1;
	res.tm_mon = month;
	res.tm_year = year - 1900;
	res.tm_wday = wday;
	res.tm_yday = yday;

	res.tm_isdst = 0;
	res.tm_gmtoff = 0L;
	res.tm_zone = (char *)0L;

	return (res);
}
#endif

#ifdef L_tm2mjd
/* from caldate_mjd libtai-0.60 */
/* hacked up for time_t-64 support */

static unsigned times365[4] = {
	0, 365, 730, 1095
};
static unsigned times36524[4] = {
	0, 36524UL, 73048UL, 109572UL
};
/* month length after february is (306 * m + 5) / 10 */
static unsigned montab[12] = {
	0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337
};

mjd_t
tm2mjd(struct tm tm)
{
	time_t d;
	int m, y;
	mjd_t res;

	if (__predict_false((d = tm.tm_year + 1900LL) < 0))
		++d;
	m = tm.tm_mon;
	y = (int)(d % 400LL);
	d = 146097LL * (d / 400) + tm.tm_mday - 678882LL;
	res.sec = tm.tm_sec + 60 * tm.tm_min + 3600 * tm.tm_hour
	    - tm.tm_gmtoff;

	while (__predict_false(res.sec < 0L)) {
		res.sec += 86400L;
		--d;
	}
	while (__predict_false(res.sec > 86400L)) {
		res.sec -= 86400L;
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

	res.mjd = d + times36524[y & 3];

	return (res);
}
#endif
