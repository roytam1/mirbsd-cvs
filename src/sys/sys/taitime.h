/* $MirOS: src/sys/sys/taitime.h,v 1.3 2007/08/08 18:48:48 tg Exp $ */

/*-
 * Copyright (c) 2007, 2011
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
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

#ifndef _SYS_TAITIME_H_
#define _SYS_TAITIME_H_

/*
 * Represents the current date and time of day in seconds
 * since 1970-01-01 00:00:00 (beginning of the TAI year),
 * as a biased signed 63 bit value.
 */
#define __TAI64_BIAS	0x4000000000000000ULL
typedef	int64_t tai64_t;

/* MirBSD bonus: flag used by the code to accept a wrap-around extension */
#define __TAI_CAN_BE_64BIT

/* tai64_t + nanosecond and attosecond accuracy */
typedef	struct {
	tai64_t secs;
	uint32_t nano;
	uint32_t atto;
} tai64na_t;

/* Modified Julian Date */
typedef struct {
	time_t	mjd;
	int32_t	sec;
} mjd_t;

#if !defined(__STRUCT_TM_DECLARED)
struct tm {
	int tm_sec;		/* seconds [0-60] */
	int tm_min;		/* minutes [0-59] */
	int tm_hour;		/* hours [0-23] */
	int tm_mday;		/* day of month [1-31] */
	int tm_mon;		/* month of year - 1 [0-11] */
	time_t tm_year;		/* year - 1900 */
	int tm_wday;		/* day of week (0 = sunday) */
	int tm_yday;		/* day of year [0-365] */
	int tm_isdst;		/* summer time effective? [0/1] */
	long tm_gmtoff;		/* offset from UTC in seconds */
	char *tm_zone;		/* abbreviation of timezone name */
};
#define __STRUCT_TM_DECLARED
#endif

#if defined(_KERNEL) || __OPENBSD_VISIBLE
__BEGIN_DECLS
/* leap second array management */
tai64_t *tai_leaps(void);
int tai_isleap(tai64_t);

/* basic conversion */
tai64_t timet2tai(time_t);
time_t tai2timet(tai64_t);

/* advanced conversion */
tai64_t utc2tai(int64_t);
int64_t tai2utc(tai64_t);
tai64_t mjd2tai(mjd_t);
mjd_t tai2mjd(tai64_t);
struct tm mjd2tm(mjd_t);
mjd_t tm2mjd(struct tm);
__END_DECLS

#define timet2tai(x)	((tai64_t)((time_t)(x) + __TAI64_BIAS))
#define tai2timet(x)	((time_t)((tai64_t)(x) - __TAI64_BIAS))
#endif /* _KERNEL || __OPENBSD_VISIBLE */

#if !defined(_KERNEL) && __OPENBSD_VISIBLE
__BEGIN_DECLS
/* get current time */
tai64_t tai_time(tai64_t *)
    __attribute__((bounded (minbytes, 1, 8)));
void taina_time(tai64na_t *)
    __attribute__((bounded (minbytes, 1, 16)));

/* on-the-wire DJB-compatible conversion */
void exporttai(uint8_t *, tai64na_t *)
    __attribute__((bounded (minbytes, 1, 16)))
    __attribute__((bounded (minbytes, 2, 16)));
void importtai(uint8_t *, tai64na_t *)
    __attribute__((bounded (minbytes, 1, 16)))
    __attribute__((bounded (minbytes, 2, 16)));
__END_DECLS
#endif /* !_KERNEL && __OPENBSD_VISIBLE */

#endif
