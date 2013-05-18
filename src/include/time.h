/**	$MirOS: src/include/time.h,v 1.3 2005/11/21 19:31:54 tg Exp $ */
/*	$OpenBSD: time.h,v 1.16 2003/08/01 17:38:33 avsm Exp $	*/
/*	$NetBSD: time.h,v 1.9 1994/10/26 00:56:35 cgd Exp $	*/

/*
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)time.h	5.12 (Berkeley) 3/9/91
 */

#ifndef _TIME_H_
#define	_TIME_H_

#include <machine/types.h>
#include <machine/ansi.h>

#ifndef	NULL
#ifdef 	__GNUG__
#define	NULL	__null
#elif defined(lint)
#define	NULL	0
#else
#define	NULL	((void *)((__PTRDIFF_TYPE__)0UL))
#endif
#endif

#ifdef	_BSD_CLOCK_T_
typedef	_BSD_CLOCK_T_	clock_t;
#undef	_BSD_CLOCK_T_
#endif

#ifdef	_BSD_TIME_T_
typedef	_BSD_TIME_T_	time_t;
#undef	_BSD_TIME_T_
#endif

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__	size_t;
#endif

#define CLOCKS_PER_SEC	100

struct tm {
	int	tm_sec;		/* seconds after the minute [0-60] */
	int	tm_min;		/* minutes after the hour [0-59] */
	int	tm_hour;	/* hours since midnight [0-23] */
	int	tm_mday;	/* day of the month [1-31] */
	int	tm_mon;		/* months since January [0-11] */
	time_t	tm_year;	/* years since 1900 */
	int	tm_wday;	/* days since Sunday [0-6] */
	int	tm_yday;	/* days since January 1 [0-365] */
	int	tm_isdst;	/* Daylight Saving Time flag */
	long	tm_gmtoff;	/* offset from UTC in seconds */
	char	*tm_zone;	/* timezone abbreviation */
};

#if !defined(__TIMESPEC_DECLARED)
struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
};
#define	__TIMESPEC_DECLARED
#endif

/*
 * Represents the current date and time of day in seconds
 * since 1970-01-01 00:00:00 (beginning of the TAI year),
 * with a bias of 0x4000000000000000, as a signed 63 bit value.
 */
typedef	int64_t tai64_t;

/* The same, just with nanosecond and attosecond accuracy */
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

__BEGIN_DECLS
char *asctime(const struct tm *);
clock_t clock(void);
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *);
size_t strftime(char *, size_t, const char *, const struct tm *)
		__attribute__ ((__bounded__(__string__,1,2)));
char *strptime(const char *, const char *, struct tm *);
time_t time(time_t *);
char *asctime_r(const struct tm *, char *)
		__attribute__ ((__bounded__(__minbytes__,2,26)));
char *ctime_r(const time_t *, char *)
		__attribute__ ((__bounded__(__minbytes__,2,26)));
struct tm *gmtime_r(const time_t *, struct tm *);
struct tm *localtime_r(const time_t *, struct tm *);
int nanosleep(const struct timespec *, struct timespec *);

#if !defined(_ANSI_SOURCE)
#define CLK_TCK		100
extern char *tzname[2];
void tzset(void);
#endif /* not ANSI */

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
char *timezone(int, int);
void tzsetwall(void);
time_t timelocal(struct tm *);
time_t timegm(struct tm *);
time_t timeoff(struct tm *, const long);
#endif /* neither ANSI nor POSIX */

/*
 * tai64 and mjd handling functions
 */

/* Get current time */
tai64_t	tai_time(tai64_t *)
		__attribute__((__bounded__(__minbytes__,1,8)));
void	taina_time(tai64na_t *)
		__attribute__((__bounded__(__minbytes__,1,16)));
tai64_t *tai_leaps(void);
int	tai_isleap(tai64_t);

/* Conversion routines */
#define __TAI64_BIAS	0x4000000000000000ULL
/* these are normally macros */
tai64_t	timet2tai(time_t);
#define	timet2tai(x)	((tai64_t)((time_t)(x) + __TAI64_BIAS))
time_t	tai2timet(tai64_t);
#define	tai2timet(x)	((time_t)((tai64_t)(x) - __TAI64_BIAS))
tai64_t	utc2tai(int64_t);
int64_t	tai2utc(tai64_t);
tai64_t	mjd2tai(mjd_t);
mjd_t	tai2mjd(tai64_t);

struct tm mjd2tm(mjd_t);
mjd_t tm2mjd(struct tm);

/* Conversion between tai64 and DJB-compatible TAI64NA on the wire values */
void	exporttai(uint8_t *, tai64na_t *)
		__attribute__((__bounded__(__minbytes__,1,16)))
		__attribute__((__bounded__(__minbytes__,2,16)));
void	importtai(uint8_t *, tai64na_t *)
		__attribute__((__bounded__(__minbytes__,1,16)))
		__attribute__((__bounded__(__minbytes__,2,16)));
__END_DECLS

#endif /* !_TIME_H_ */
