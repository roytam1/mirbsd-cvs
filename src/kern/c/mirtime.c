/*-
 * Copyright © 2004, 2005, 2006, 2007, 2011
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * MirBSD new time functions (common part, mirtime_getleaps is system
 * specific). The code to convert betwen MJD and broken-down calendar
 * dates is a re-implementation of algorithms from Dan J. Bernstein.
 *
 * This code works by the assumption that leap seconds are always po‐
 * sitive and happen at most once per cluster (no double leapsecs).
 */

#include <sys/types.h>
#include <syskern/mirtime.h>

__RCSID("$MirOS: src/kern/c/mirtime.c,v 1.1 2011/11/20 04:57:09 tg Exp $");

#ifdef L_timet2posix
time_t
timet2posix(time_t t)
{
	time_t u = t;
	const time_t *lp;

	if (__predict_true(t > 0)) {
		lp = mirtime_getleaps();
		while (__predict_true((*lp) && (t >= *lp))) {
			--u;
			++lp;
		}
	}
	return (u);
}
#endif

#ifdef L_posix2timet
time_t
posix2timet(time_t t)
{
	const time_t *lp;

	if (__predict_true(t > 0)) {
		lp = mirtime_getleaps();
		while (__predict_true((*lp) && (t >= *lp))) {
			++t;
			++lp;
		}
	}
	return (t);
}
#endif

#ifdef L_timet2mjd
mirtime_mjd *
timet2mjd(mirtime_mjd *mjd, time_t t)
{
	time_t u;

	/* POSIX time inherent property: days have 86400 seconds */
	u = timet2posix(t);
	mjd->sec = (int32_t)(u % 86400);
	u /= 86400;
	u += 40587;

	/* normalise */
	while (__predict_false(mjd->sec < 0)) {
		--u;
		mjd->sec += 86400;
	}

	/* account for a possible leap second */
	if (__predict_false(mirtime_isleap(t)))
		++mjd->sec;

	mjd->mjd = u;
	return (mjd);
}
#endif

#ifdef L_mjd2timet
time_t
mjd2timet(mirtime_mjd *mjd)
{
	time_t t;

	/* construct a POSIX timestamp again */
	t = mjd->mjd;
	t -= 40587;
	t *= 86400;
	t += (mjd->sec > 86399 ? 86399 : mjd->sec);

	/* add leap seconds between epoch and t */
	t = posix2timet(t);

	/* if mjd was a leap second, account for it */
	if (mjd->sec > 86399)
		++t;

	return (t);
}
#endif

#ifdef L_mjd_explode
struct tm *
mjd_explode(struct tm *tm, mirtime_mjd *mjd)
{
	int sec, day, yday, mon;
	time_t year;

	year = mjd->mjd;
	sec = mjd->sec;

	/* normalise */
	while (sec < 0) {
		--year;
		sec += 86400;
	}
	while (sec > 86400) {
		++year;
		sec -= 86400;
	}

	/* buffer leap second */
	tm->tm_sec = (sec == 86400) ? 1 : 0;
	sec -= tm->tm_sec;

	/* calculate 400-year cycle (year) and offset in it (day) */
	day = (int)(year % 146097);
	year /= 146097;

	/* add bias: 678881 = days between "convenient origin" and MJD 0 */
	/* convenient origin is Wed(3) 1 March 0(fictional)/-1(real) */
	day += 678881;
	/* recalculate offset in cycle (Gregorian Period) */
	year += day / 146097;
	day %= 146097;

	/* days in 400 years are cyclic, they have 20871 weeks */
	tm->tm_wday = (day + 3) % 7;

	/* calculate year from period, taking leap years into account */
	year *= 4;
	/* a long (Julian) century is at the end of each Gregorian Period */
	if (__predict_false(day == 146096)) {
		year += 3;
		day = 36524;
	} else {
		year += day / 36524;
		day %= 36524;
	}
	year *= 25;
	year += day / 1461;
	day %= 1461;
	year *= 4;

	/* March to December, or January/February? */
	yday = (day < 306) ? 1 : 0;
	/* a leap year is at the end of each olympiad */
	if (__predict_false(day == 1460)) {
		year += 3;
		day = 365;
	} else {
		year += day / 365;
		day %= 365;
	}
	yday += day;

	/* count days and months from 1st March using fixed-point */
	day *= 10;
	mon = (day + 5) / 306;
	day = (day + 5) % 306;
	day /= 10;
	/* adjust for Jan/Feb offset */
	if (__predict_false(mon >= 10)) {
		mon -= 10;
		yday -= 306;
		++year;
	} else {
		mon += 2;
		yday += 31 + 28;
	}

	/* adjust for year 0(fictional) which did not exist */
	if (__predict_false(year < 1))
		--year;

	/* fill in the values still missing */
	tm->tm_sec += sec % 60;
	sec /= 60;
	tm->tm_min = sec % 60;
	tm->tm_hour = sec / 60;
	tm->tm_mday = day + 1;
	tm->tm_mon = mon;
	tm->tm_year = year - 1900;
	tm->tm_yday = yday;
	/* hardcode these */
	tm->tm_isdst = 0;
	tm->tm_gmtoff = 0;
	tm->tm_zone = (void *)0L;
	/* return dst */
	return (tm);
}
#endif

#ifdef L_mjd_implode
mirtime_mjd *
mjd_implode(mirtime_mjd *mjd, struct tm *tm)
{
	time_t day;
	int x, y;

	/* get the seconds out first */
	mjd->sec = tm->tm_sec + 60 * tm->tm_min + 3600 * tm->tm_hour -
	    tm->tm_gmtoff;

	/* pull the year; adjust for year 0 not existing */
	if (__predict_false((day = tm->tm_year + 1900LL) < 0))
		++day;

	/* split year into y(ear in Gregorian Period) and convenient day */
	y = day % 400;
	day /= 400;
	day *= 146097;
	day -= 678882;
	/* add day of month */
	day += tm->tm_mday;

	/* normalise seconds into days */
	while (__predict_false(mjd->sec < 0)) {
		--day;
		mjd->sec += 86400;
	}
	while (__predict_false(mjd->sec > 86400)) {
		++day;
		mjd->sec -= 86400;
	}

	/* assign x the month and normalise into years */
	x = tm->tm_mon;
	while (__predict_false(x < 0)) {
		--y;
		x += 12;
	}
	y += x / 12;
	x %= 12;

	/* calculate x as month since march, adjust year for it */
	if (__predict_false(x < 2)) {
		x += 10;
		--y;
	} else
		x -= 2;

	/* add length of month since march by fixed-point arithmetic */
	day += (306 * x + 5) / 10;

	/* normalise 400-year cycles again */
	while (__predict_false(y < 0)) {
		day -= 146097;
		y += 400;
	}
	day += 146097 * (y / 400);
	y %= 400;

	/* add by year, 4 years, 100 years, 400 years */
	day += 365 * (y % 4);
	y /= 4;
	day += 1461 * (y % 25);
	day += 36524 * (y / 25);

	mjd->mjd = day;
	/* return dst */
	return (mjd);
}
#endif

#ifdef L_mirtime_isleap
int
mirtime_isleap(time_t t)
{
	time_t lt;
	const time_t *lp;

	lp = mirtime_getleaps();
	while (__predict_true((lt = *lp))) {
		if (__predict_false(t < lt))
			return (0);
		else if (__predict_false(t == lt))
			return (1);
		else
			++lp;
	}
	return (0);
}
#endif

#ifdef L_mirtime_macrobodies
#undef timet2tm
#undef tm2timet
struct tm *
timet2tm(struct tm *dst, time_t src)
{
	mirtime_mjd timet2tm_storage;

	return (mjd_explode(dst, timet2mjd(&timet2tm_storage, src)));
}

time_t
tm2timet(struct tm *src)
{
	mirtime_mjd tm2timet_storage;

	return (mjd2timet(mjd_implode(&tm2timet_storage, src)));
}
#endif
