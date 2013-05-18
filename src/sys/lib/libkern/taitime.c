/* $MirOS: src/sys/lib/libkern/taitime.c,v 1.3 2006/06/12 21:51:48 tg Exp $ */
/* _MirOS: src/lib/libc/time/taitime.c,v 1.7 2006/11/01 20:01:21 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Based upon code placed into the public domain by
 *	Dan J. Bernstein <djb@cr.yp.to>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <lib/libkern/taitime.h>

tai64_t
utc2tai(int64_t u)
{
	tai64_t t = u + __TAI64_BIAS;
	tai64_t *s = _tai_leaps();

	if (__predict_true(u > 0))
		while (__predict_true((*s) && (t >= *s))) {
			++t;
			++s;
		}
	return (t);
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

	return (u);
}

int
tai_isleap(tai64_t x)
{
	tai64_t *t;

	t = _tai_leaps();
	while (__predict_true(*t))
		if (__predict_false((*t) == x))
			return (1);
		else if (__predict_false((*t) > x))
			return (0);
		else
			++t;
	return (0);
}

tai64_t
mjd2tai(mjd_t m)
{
	int64_t x = (m.mjd - 40587LL) * 86400LL;
	tai64_t t;

	x += (m.sec > 86399) ? 86399 : m.sec;
	t = utc2tai(x);
	if (m.sec > 86399)
		++t;

	return (t);
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

	return (m);
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

	bzero(&res, sizeof(res));

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

	return (res);
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
	mjd_t res;

	if (__predict_false(d < 0))
		++d;
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
