#if 0
.if "0" == "1"
#endif

/*-
 * Copyright (c) 2011
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

static void buftime(register const struct tm *timeptr);
static int usage(void);

char buf[1048576];

int
main(int argc, char *argv[])
{
	time_t t;
	struct tm tm, *ptm;

	if (argc != 4 || !argv[1][0] || argv[1][1])
		return (usage());

	switch (argv[1][0]) {
	/* strftime */
	case 'f':
		t = atoll(argv[3]);
		if ((ptm = gmtime(&t)) == NULL) {
			printf("%lld is NULL\n", (long long)t);
			return (255);
		}
		strftime(buf, sizeof(buf), argv[2], ptm);
		printf("%lld\n%s\n", (long long)t, buf);
		return (0);

	/* strptime */
	case 'p':
		if (strptime(argv[3], argv[2], ptm = &tm) == NULL) {
			printf("NULL\n");
			return (255);
		}
		buftime(ptm);
		t = mktime(ptm);
		printf("%lld\n%s\n", (long long)t, buf);
		return (0);

	}
	return (usage());
}

extern const char *__progname;
static int
usage(void)
{
	fprintf(stderr, "Usage:\t%s f formatstring timetvalue\n"
	    "\t%s p formatstring formattedvalue\n", __progname, __progname);
	return (1);
}

/* from MirBSD libc/time, modified */
static void
buftime(register const struct tm *timeptr)
{
	static const char	wday_name[][3] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char	mon_name[][3] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	register const char *	wn;
	register const char *	mn;
#ifndef TM_YEAR_BASE
#define TM_YEAR_BASE	1900
#endif

	/*
	** The packaged versions of localtime and gmtime never put out-of-range
	** values in tm_wday or tm_mon, but since this code might be compiled
	** with other (perhaps experimental) versions, paranoia is in order.
	*/
	if (timeptr->tm_wday < 0 || timeptr->tm_wday >=
		(int) (sizeof wday_name / sizeof wday_name[0]))
			wn = "???";
	else		wn = wday_name[timeptr->tm_wday];
	if (timeptr->tm_mon < 0 || timeptr->tm_mon >=
		(int) (sizeof mon_name / sizeof mon_name[0]))
			mn = "???";
	else		mn = mon_name[timeptr->tm_mon];
	snprintf(buf, sizeof(buf),
	    "%.3s %.3s%3d (%d) %lld %.2d:%.2d:%.2d %s (%ld%s)",
	    wn, mn, timeptr->tm_mday, timeptr->tm_yday,
	    (int64_t)timeptr->tm_year + (long long) TM_YEAR_BASE,
	    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec,
	    timeptr->tm_zone ? timeptr->tm_zone : "(null)",
	    timeptr->tm_gmtoff,
	    timeptr->tm_isdst ? " DST" : "");
}

#if 0
.endif

PROG=		strtime
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
