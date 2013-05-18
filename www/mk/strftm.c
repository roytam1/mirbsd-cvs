/*-
 * Copyright (c) 2008
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

#include <sys/param.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

__RCSID("$MirOS: www/mk/strftm.c,v 1.1 2008/11/08 16:28:46 tg Exp $");

extern const char *__progname;

char buf[4096];

#define CONVERT(num, elem, name, minval, maxval) do {			\
	const char *e = NULL;						\
	char *ep;							\
	long long res;							\
									\
	tm.elem = res = strtoll(argv[num], &ep, 0);			\
	if (ep == argv[num] || *ep != '\0')				\
		e = "invalid";						\
	else if ((res == LLONG_MIN && errno == ERANGE) ||		\
	    res < (minval))						\
		e = "too small";					\
	else if ((res == LLONG_MAX && errno == ERANGE) ||		\
	    res > (maxval))						\
		e = "too large";					\
	if (e != NULL)							\
		errx(2, "%s value 「%s」 is %s", (name), argv[num], e);	\
} while (/* CONSTCOND */ 0)

int
main(int argc, char *argv[])
{
	struct tm tm;
	time_t t;

	if (argc != 8)
		errx(1, "syntax: %s fmtstr y m d h m s\n", __progname);

	memset(&tm, '\0', sizeof (struct tm));

	CONVERT(2, tm_year, "year", LONG_MIN, LONG_MAX - 1900);
	CONVERT(3, tm_mon, "month", 1, 12);
	CONVERT(4, tm_mday, "day", 1, 31);
	CONVERT(5, tm_hour, "hour", 0, 23);
	CONVERT(6, tm_min, "minute", 0, 59);
	CONVERT(7, tm_sec, "second", 0, 60);

	tm.tm_year -= 1900;
	--tm.tm_mon;

	if ((t = mktime(&tm)) == (time_t)-1)
		errx(2, "invalid calendar time %04lld-%02d-%02d %02d:%02d:%02d",
		    (long long)tm.tm_year + 1900LL, tm.tm_mon + 1, tm.tm_mday,
		    tm.tm_hour, tm.tm_min, tm.tm_sec);

	localtime_r(&t, &tm);

	if (!strftime(buf, sizeof (buf), argv[1], &tm))
		errx(3, "format string 「%s」 too large", argv[1]);

	puts(buf);
	return (0);
}
