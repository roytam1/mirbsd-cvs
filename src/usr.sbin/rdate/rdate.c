/**	$MirOS: src/usr.sbin/rdate/rdate.c,v 1.2 2005/03/13 19:17:21 tg Exp $ */
/*	$OpenBSD: rdate.c,v 1.22 2004/02/18 20:10:53 jmc Exp $	*/
/*	$NetBSD: rdate.c,v 1.4 1996/03/16 12:37:45 pk Exp $	*/

/*
 * Copyright (c) 2005 Thorsten Glaser
 * Copyright (c) 1994 Christos Zoulas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Christos Zoulas.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * rdate.c: Set the date from the specified host
 *
 *	Uses the rfc868 time protocol at socket 37.
 *	Time is returned as the number of seconds since
 *	midnight January 1st 1900.
 */

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* there are systems without libutil; for portability */
#ifndef	NO_UTIL
#include <util.h>
#else
#define	logwtmp(a,b,c)
#endif

__RCSID("$MirOS$");

void rfc868time_client(const char *, int, struct timeval *, struct timeval *, int);
void ntp_client(const char *, int, struct timeval *, struct timeval *, int);
void usage(void);

extern char *__progname;

void
usage(void)
{
	(void) fprintf(stderr, "Usage: %s [-46acnpsv] host\n", __progname);
	(void) fprintf(stderr, "  -4: use IPv4 only\n");
	(void) fprintf(stderr, "  -6: use IPv6 only\n");
	(void) fprintf(stderr, "  -a: use adjtime instead of instant change\n");
	(void) fprintf(stderr, "  -c: correct leap second count (recommended)\n");
	(void) fprintf(stderr, "  -n: use SNTP instead of RFC868 time protocol\n");
	(void) fprintf(stderr, "  -p: just print, don't set\n");
	(void) fprintf(stderr, "  -r: show remainder from last adjtime\n");
	(void) fprintf(stderr, "  -s: just set, don't print (overrides -v)\n");
	(void) fprintf(stderr, "  -v: verbose output (clears -s)\n");
}

int
main(int argc, char **argv)
{
	int             pr = 0, silent = 0, ntp = 0, verbose = 0;
	int		slidetime = 0, corrleaps = 0, showremainder = 0;
	char           *hname;
	int             c;
	int		family = PF_UNSPEC;

	struct timeval new, adjust, remainder;

	while ((c = getopt(argc, argv, "46acnprsv")) != -1)
		switch (c) {
		case '4':
			family = PF_INET;
			break;

		case '6':
			family = PF_INET6;
			break;

		case 'p':
			pr++;
			break;

		case 'r':
			showremainder++;
			break;

		case 's':
			silent++;
			break;

		case 'a':
			slidetime++;
			break;

		case 'n':
			ntp++;
			break;

		case 'c':
			corrleaps++;
			break;

		case 'v':
			verbose++;
			silent = 0;
			break;

		default:
			usage();
			return 1;
		}

	if ((argc - 1) != optind) {
		usage();
		return 1;
	}
	hname = argv[optind];

	if (ntp)
		ntp_client(hname, family, &new, &adjust, corrleaps);
	else
		rfc868time_client(hname, family, &new, &adjust, corrleaps);

	if (!pr) {
		if (!slidetime) {
			logwtmp("|", "date", "");
			if (settimeofday(&new, NULL) == -1)
				err(1, "Could not set time of day");
			logwtmp("{", "date", "");
		} else {
			if (adjtime(&adjust, &remainder) == -1)
				err(1, "Could not adjust time of day");
		}
	}

	if (!silent) {
		struct tm      *ltm;
		char		buf[80];
		time_t		tim = new.tv_sec;
		double		adjsec, remainsec;

		ltm = localtime(&tim);
		(void) strftime(buf, sizeof buf, "%a %b %e %H:%M:%S %Z %Y\n", ltm);
		(void) fputs(buf, stdout);

		adjsec  = adjust.tv_sec + adjust.tv_usec / 1.0e6;
		remainsec  = remainder.tv_sec + remainder.tv_usec / 1.0e6;

		if (slidetime || verbose) {
			if (ntp)
				(void) fprintf(stdout,
				   "%s: adjust local clock by %.6f seconds\n",
				   __progname, adjsec);
			else
				(void) fprintf(stdout,
				   "%s: adjust local clock by %ld seconds\n",
				   __progname, (long)adjust.tv_sec);
		}
		if (!pr && slidetime && showremainder)
			(void) fprintf(stdout,
			    "%s: remainder before was %.6f seconds\n",
			    __progname, remainsec);
	}

	if (!corrleaps) {
		(void) fprintf(stderr,
		    "%s: WARNING: Not using the '-c' parameter is deprecated and can\n"
		    "lead to the clock being set wrongly (even if sometimes POSIXly correct)\n",
		    __progname);
		if (!ntp) fprintf(stderr,
		    "This does not apply if the time server uses corrected leap seconds.\n");
	}

	return 0;
}
