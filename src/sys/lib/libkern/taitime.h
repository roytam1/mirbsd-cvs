/**	$MirOS: src/include/time.h,v 1.5 2006/06/12 21:46:33 tg Exp $ */
/**	_MirOS: src/include/time.h,v 1.5 2006/06/12 21:46:33 tg Exp $ */
/*	$OpenBSD: time.h,v 1.16 2003/08/01 17:38:33 avsm Exp $	*/
/*	$NetBSD: time.h,v 1.9 1994/10/26 00:56:35 cgd Exp $	*/

/*
 * Copyright (c) 2004, 2005, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *
 *	@(#)time.h	5.12 (Berkeley) 3/9/91
 */

#ifndef _LIBKERN_TAITIME_H_
#define	_LIBKERN_TAITIME_H_

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

/*
 * Represents the current date and time of day in seconds
 * since 1970-01-01 00:00:00 (beginning of the TAI year),
 * with a bias of 0x4000000000000000, as a signed 63 bit value.
 */
typedef	int64_t tai64_t;

/* Modified Julian Date */
typedef struct {
	time_t	mjd;
	int32_t	sec;
} mjd_t;

__BEGIN_DECLS
tai64_t *_tai_leaps(void);
int	tai_isleap(tai64_t);

/* in-core basic conversion */
#define __TAI64_BIAS	0x4000000000000000ULL
/* these are normally macros */
tai64_t	timet2tai(time_t);
#define	timet2tai(x)	((tai64_t)((time_t)(x) + __TAI64_BIAS))
time_t	tai2timet(tai64_t);
#define	tai2timet(x)	((time_t)((tai64_t)(x) - __TAI64_BIAS))

/* in-core advanced conversion */
tai64_t	utc2tai(int64_t);
int64_t	tai2utc(tai64_t);
tai64_t	mjd2tai(mjd_t);
mjd_t	tai2mjd(tai64_t);
struct tm mjd2tm(mjd_t);
mjd_t tm2mjd(struct tm);
__END_DECLS

#endif /* !_LIBKERN_TAITIME_H_ */
