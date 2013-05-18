/* $MirOS: src/usr.sbin/rdate/leapsecs.c,v 1.1 2006/05/29 23:38:31 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Based upon code placed into the public domain by Dan J. Bernstein.
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/types.h>
#include <sys/time.h>
#include <inttypes.h>
#include <time.h>

#include "ntpleaps.h"

#ifndef __RCSID
#define	__RCSID(x)	static const char __rcsid[] __attribute__((used)) = (x)
#endif

__RCSID("$MirOS: src/usr.sbin/rdate/leapsecs.c,v 1.1 2006/05/29 23:38:31 tg Exp $");

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
