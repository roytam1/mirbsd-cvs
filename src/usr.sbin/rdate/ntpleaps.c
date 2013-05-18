/* $MirOS: src/usr.sbin/rdate/ntpleaps.c,v 1.7 2007/05/14 22:06:52 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Based upon code placed into the public domain by Dan J. Bernstein.
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
#include <sys/time.h>
#include <inttypes.h>
#include <time.h>

__RCSID("$MirOS: src/usr.sbin/rdate/ntpleaps.c,v 1.7 2007/05/14 22:06:52 tg Exp $");

time_t tick2utc(time_t);

/*
 * Converts a time_t measured in kernel ticks into a UTC time_t
 * using leap second information stored in /etc/localtime or an
 * equivalent indicator (e.g. the TZ environment variable).
 * If the kernel time is already measured in UTC instead of TAI
 * and a POSIX conformant time zone is set, this is a no-op.
 */
time_t
tick2utc(time_t kerneltick)
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

	struct tm *tm;
	int64_t utc, d = 1900;
	int m, y;

	tm = localtime(&kerneltick);
	d += tm->tm_year;

	if (d < 0)
		++d;
	y = (int)(d % 400LL);
	d = 146097LL * (d / 400) + tm->tm_mday - 678882LL;
	utc = tm->tm_sec - tm->tm_gmtoff + 60 * (tm->tm_min + 60 * tm->tm_hour);

	while (utc < 0L) {
		utc += 86400L;
		--d;
	}
	while (utc > 86400L) {
		utc -= 86400L;
		++d;
	}

	if ((m = tm->tm_mon) >= 2) {
		m -= 2;
	} else {
		m += 10;
		--y;
	}

	y += (m / 12);
	m %= 12;
	if (m < 0) {
		m += 12;
		--y;
	}
	d += montab[m];

	d += 146097LL * (y / 400LL);
	y %= 400;
	while (y < 0) {
		y += 400;
		d -= 146097LL;
	}

	d += times365[y & 3];
	y /= 4;

	d += 1461LL * (y % 25);
	y /= 25;

	d += times36524[y & 3];

	/*
	 * d now contains the date part of the MJD
	 * corresponding to tm / kerneltick; the
	 * second part is already stored in utc.
	 */

	utc += (d - 40587LL) * 86400LL;
	return (utc);
}
