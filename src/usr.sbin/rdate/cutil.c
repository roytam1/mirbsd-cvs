/*-
 * Copyright (c) 2010, 2011, 2012
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
 *-
 * Helper functions shared between rdate(8) and ntpd(8) partially de-
 * rived from OpenNTPD code by Henning Brauer.
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef IN_RDATE
#include "rdate.h"
#else
#include "ntpd.h"
#endif

__RCSID("$MirOS: src/usr.sbin/rdate/cutil.c,v 1.2 2011/11/21 20:49:38 tg Exp $");

const char *
log_sockaddr(struct sockaddr *sa)
{
	static char buf[NI_MAXHOST + 8];
	struct sockinet {
		uint8_t si_len;
		uint8_t si_family;
		uint8_t si_port[2];
	} *si = (struct sockinet *)sa;
	unsigned short s_port;

#ifdef IN_NTPD
	/* traditional ntpd style */
#define gnibuf		buf
#define portfmtstr	"*%u"
#else
	/* classic output style */
#define gnibuf		(buf + 1)
#define portfmtstr	"]:%u"
	buf[0] = '[';
#endif

	if (sa == NULL || sa == (void *)(ptrdiff_t)(sizeof(void *)))
		return ("(not set)");

	if (getnameinfo(sa, SA_LEN(sa), gnibuf, NI_MAXHOST, NULL, 0,
	    NI_NUMERICHOST))
		return ("(unknown)");

	memcpy(&s_port, &si->si_port, sizeof(unsigned short));
	s_port = ntohs(s_port);
	if (!s_port || s_port == 123)
		/* don't print port as it's default or empty */
		return (gnibuf);

	/* append port and return whole string */
	snprintf(buf + strlen(buf), 8, portfmtstr, (unsigned int)s_port);
	return (buf);
}

/* get the current POSIX time in NTP format */
double
gettime(void)
{
	register double d;
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		err(1, "Could not get local time of day");
	d = tv.tv_usec;
	d /= 1000000;
	d += timet2posix(tv.tv_sec);
	/* 1970 - 1900 in POSIX seconds */
	d += 2208988800.0;
	return (d);
}
