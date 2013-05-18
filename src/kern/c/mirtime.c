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

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

#ifdef L_timet2posix
time_t
timet2posix(time_t t)
{
	time_t u = t, *lp;

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
	time_t *lp;

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
	mjd->mjd = (u / 86400) + (time_t)40587;

	/* normalise */
	while (__predict_false(mjd->sec < 0)) {
		mjd->sec += 86400;
		--mjd->mjd;
	}

	/* account for a possible leap second */
	if (__predict_false(mirtime_isleap(t)))
		++mjd->sec;

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
	/*XXX todo */
	return (NULL);
}
#endif

#ifdef L_mjd_implode
mirtime_mjd *
mjd_implode(mirtime_mjd *mjd, struct tm *tm)
{
	/*XXX todo */
	return (NULL);
}
#endif

#ifdef L_mirtime_isleap
int
mirtime_isleap(time_t t)
{
	time_t lt, *lp;

	lp = mirtime_getleaps();
	while (__predict_true((lt = *lp))) {
		if (__predict_false(t < lt))
			return (0)
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
