/*-
 * Copyright (c) 2004, 2005, 2006, 2007, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
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

#include <sys/types.h>
#define _IN_TAITIME_IMPLEMENTATION
#include <sys/taitime.h>

__RCSID("$MirOS: src/kern/c/taitime.c,v 1.5 2011/10/29 00:32:27 tg Exp $");

#ifdef L_tai_isleap
int
tai_isleap(tai64_t x)
{
	return (mirtime_isleap(tai2timet(x)));
}
__warn_references(tai_isleap, "tai_isleap is deprecated; use the new mirtime API instead");
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
__warn_references(timet2tai, "timet2tai is deprecated; use the new mirtime API instead");
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
__warn_references(tai2timet, "tai2timet is deprecated; use the new mirtime API instead");
#endif

#ifdef L_utc2tai
tai64_t
utc2tai(int64_t u)
{
	return (timet2tai(posix2timet(u)));
}
__warn_references(utc2tai, "utc2tai is deprecated; use the new mirtime API instead");
#endif

#ifdef L_tai2utc
int64_t
tai2utc(tai64_t t)
{
	return (timet2posix(tai2timet(t)));
}
__warn_references(tai2utc, "tai2utc is deprecated; use the new mirtime API instead");
#endif

#ifdef L_mjd2tai
tai64_t
mjd2tai(mjd_t m)
{
	return (timet2tai(mjd2timet(&m)));
}
__warn_references(mjd2tai, "mjd2tai is deprecated; use the new mirtime API instead");
#endif

#ifdef L_tai2mjd
mjd_t
tai2mjd(tai64_t tai)
{
	mjd_t m;

	timet2mjd(&m, tai2timet(tai));
	return (m);
}
__warn_references(tai2mjd, "tai2mjd is deprecated; use the new mirtime API instead");
#endif

#ifdef L_mjd2tm
struct tm
mjd2tm(mjd_t m)
{
	struct tm res;

	mjd_explode(&res, &m);
	return (res);
}
__warn_references(mjd2tm, "mjd2tm is deprecated; use the new mirtime API instead");
#endif

#ifdef L_tm2mjd
mjd_t
tm2mjd(struct tm tm)
{
	mjd_t res;

	mjd_implode(&res, &tm);
	return (res);
}
__warn_references(tm2mjd, "tm2mjd is deprecated; use the new mirtime API instead");
#endif
