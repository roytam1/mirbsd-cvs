/* $MirOS: src/gnu/usr.bin/rcs/src/rcstime.c,v 1.3 2007/02/08 07:09:55 tg Exp $ */

/* Convert between RCS time format and Posix and/or C formats.  */

/* Copyright 1992, 1993, 1994, 1995 Paul Eggert
   Distributed under license by the Free Software Foundation, Inc.

This file is part of RCS.

RCS is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

RCS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RCS; see the file COPYING.
If not, write to the Free Software Foundation,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

Report problems and direct all questions to:

    rcs-bugs@cs.purdue.edu

*/

#include "rcsbase.h"
#include "getdate.h"

__RCSID("$MirOS: src/gnu/usr.bin/rcs/src/rcstime.c,v 1.3 2007/02/08 07:09:55 tg Exp $");

/*
* Convert Unix time to RCS format.
* For compatibility with older versions of RCS,
* dates from 1900 through 1999 are stored without the leading "19".
*/
	void
time2date(time_t unixtime, char date[datesize])
{
	struct tm tm;

	timet2tm(&tm, unixtime);
	snprintf(date, datesize,
	    "%.2d.%.2d.%.2d.%.2d.%.2d.%.2d",
	    (int)(tm.tm_year + ((unsigned)tm.tm_year < 100 ? 0 : 1900)),
	    tm.tm_mon + 1, tm.tm_mday,
	    tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static time_t
str2time_checked(char const *source, time_t default_time)
{
	struct timespec ts, td;

	td.tv_sec = default_time;
	td.tv_nsec = 0;

	if (!get_date(&ts, source, &td))
		faterror("unknown date/time: %s", source);
	return ts.tv_sec;
}

/*
* Parse a free-format date in SOURCE, convert it
* into RCS internal format, and store the result into TARGET.
*/
	void
str2date(char const *source, char target[datesize])
{
	time2date(str2time_checked(source, now()), target);
}

/* Convert an RCS internal format date to time_t.  */
	time_t
date2time(char const source[datesize])
{
	char s[datesize + zonelenmax];
	return str2time_checked(date2str(source, s), 0);
}

/*
* Format a user-readable form of the RCS format DATE into the buffer DATEBUF.
* Yield DATEBUF.
*/
	char const *
date2str(char const date[datesize], char datebuf[datesize + zonelenmax])
{
	char const *p = date;
	char *b = datebuf;

	while (*p++ != '.')
		continue;

	if (date[2]=='.' && VERSION(5)<=RCSversion) {
		strlcpy(b, "19", datesize + zonelenmax);
		b += 2;
	}

	snprintf(b, datesize + zonelenmax - (b - datebuf),
	    "%.*s/%.2s/%.2s %.2s:%.2s:%s",
	    (int)(p-date-1), date, p, p+3, p+6, p+9, p+12);
	return datebuf;
}
