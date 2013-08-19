/*	$OpenBSD: ntp.c,v 1.27 2004/10/26 09:48:59 henning Exp $	*/

/*
 * Copyright (c) 2002, 2004, 2005, 2006, 2007, 2009, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1996, 1997 by N.M. Maclaren. All rights reserved.
 * Copyright (c) 1996, 1997 by University of Cambridge. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the university may be used to
 *    endorse or promote products derived from this software without
 *    specific prior written permission.
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

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "rdate.h"

__RCSID("$MirOS: src/usr.sbin/rdate/ntp.c,v 1.21 2011/11/20 22:02:42 tg Exp $");

/*
 * NTP definitions.  Note that these assume 8-bit bytes - sigh.  There
 * is little point in parameterising everything, as it is neither
 * feasible nor useful.  It would be very useful if more fields could
 * be defined as unspecified.  The NTP packet-handling routines
 * contain a lot of extra assumptions.
 */

#define NTP_SCALE  4294967296.0		/* 2^32, of course! */

#define NTP_MODE_CLIENT       3		/* NTP client mode */
#define NTP_MODE_SERVER       4		/* NTP server mode */
#define NTP_VERSION           4		/* The current version */
#define NTP_VERSION_MIN       1		/* The minum valid version */
#define NTP_VERSION_MAX       4		/* The maximum valid version */
#define NTP_STRATUM_MAX      14		/* The maximum valid stratum */
#define NTP_INSANITY     3600.0		/* Errors beyond this are hopeless */

#define NTP_PACKET_MIN       48		/* Without authentication */
#define NTP_PACKET_MAX       68		/* With authentication (ignored) */

#define NTP_DISP_FIELD        8		/* Offset of dispersion field */
#define NTP_REFERENCE        16		/* Offset of reference timestamp */
#define NTP_ORIGINATE        24		/* Offset of originate timestamp */
#define NTP_RECEIVE          32		/* Offset of receive timestamp */
#define NTP_TRANSMIT         40		/* Offset of transmit timestamp */

#define STATUS_NOWARNING      0		/* No Leap Indicator */
#define STATUS_LEAPHIGH       1		/* Last Minute Has 61 Seconds */
#define STATUS_LEAPLOW        2		/* Last Minute Has 59 Seconds */
#define STATUS_ALARM          3		/* Server Clock Not Synchronized */

#define MAX_QUERIES         25
#define MAX_DELAY           15

#define MILLION_L    1000000l		/* For conversion to/from timeval */
#define MILLION_D       1.0e6		/* Must be equal to MILLION_L */

struct ntp_data {
	double		receive;
	double		transmit;
	double		current;
	double		originate;
	u_int64_t	xmitck;
	u_int64_t	recvck;
	u_int32_t	refid;
	u_char		status;
	u_char		version;
	u_char		mode;
	u_char		stratum;
};

static int sync_ntp(int, const struct sockaddr *, double *, double *, int);
static int write_packet(int, struct ntp_data *, int);
static int read_packet(int, struct ntp_data *, double *, double *);
static void unpack_ntp(struct ntp_data *, u_char *);
static void create_timeval(double, struct timeval *, struct timeval *);
static void debug_packet(const struct ntp_data *);
static double dabs(double);

static double
dabs(double v)
{
	return (v < 0 ? -v : v);
}

void
ntp_client(const char *hostname, int family, struct timeval *new,
    struct timeval *adjust, int sport, int nversion)
{
	struct addrinfo hints, *res0, *res;
	double offset = 0, error = 0;
	int accepts = 0, ret, s, ierror;
	union {
		struct sockaddr *s_sa;
		struct sockaddr_in *s_in;
		struct sockaddr_in6 *s_in6;
	} sun;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_DGRAM;
	ierror = getaddrinfo(hostname, "ntp", &hints, &res0);
	if (ierror) {
		errx(1, "%s: %s", hostname, gai_strerror(ierror));
		/*NOTREACHED*/
	}

	s = -1;
	for (res = res0; res; res = res->ai_next) {
		if (sport) {
			sun.s_sa = res->ai_addr;
			switch (sun.s_sa->sa_family) {
			case AF_INET:
				sun.s_in->sin_port = htons(sport);
				break;
			case AF_INET6:
				sun.s_in6->sin6_port = htons(sport);
				break;
			}
		}

		if (debug)
			fprintf(stderr, "Remote IP:   %s\n",
			    log_sockaddr(res->ai_addr));

		s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (s < 0) {
			if (debug)
				perror("Skipped:     socket");
			continue;
		}

		ret = sync_ntp(s, res->ai_addr, &offset, &error, nversion);
		if (ret < 0) {
			if (debug)
				fprintf(stderr, "Skipped:     try the next address\n");
			close(s);
			s = -1;
			continue;
		}

		accepts++;
		break;
	}
	freeaddrinfo(res0);

	if (debug)
		fprintf(stderr, "Correction:  %.6f +/- %.6f\n", offset, error);

	if (accepts < 1)
		errx(1, "Unable to get a reasonable time estimate");

	create_timeval(offset, new, adjust);
}

int
sync_ntp(int fd, const struct sockaddr *peer, double *offset, double *error,
    int nver)
{
	int attempts = 0, accepts = 0, rejects = 0;
	int delay = MAX_DELAY, ret;
	double deadline;
	double a, b, x = 0, y = 0;
	double minerr = 0.1;		/* Maximum ignorable variation */
	struct ntp_data data;

	deadline = gettime() + delay;
	*offset = 0.0;
	*error = NTP_INSANITY;

	if (connect(fd, peer, SA_LEN(peer)) < 0) {
		warn("Failed to connect to server");
		return (-1);
	}

	while (accepts < MAX_QUERIES && attempts < 2 * MAX_QUERIES) {
		memset(&data, 0, sizeof(data));

		if (gettime() > deadline) {
			warnx("Not enough valid responses received in time");
			return (-1);
		}

		if (write_packet(fd, &data, nver) < 0)
			return (-1);

		ret = read_packet(fd, &data, &x, &y);
		if (debug > 1)
			debug_packet(&data);

		if (ret < 0)
			return (-1);
		else if (ret > 0) {
			if (debug == 1)
				debug_packet(&data);
			if (++rejects > MAX_QUERIES) {
				warnx("Too many bad or lost packets");
				return (-1);
			} else
				continue;
		} else
			++accepts;

		if (debug)
			fprintf(stderr, "Offset:      %.6f +/- %.6f\n", x, y);

		if ((a = x - *offset) < 0.0)
			a = -a;
		if (accepts <= 1)
			a = 0.0;
		b = *error + y;
		if (y < *error) {
			*offset = x;
			*error = y;
		}

		if (debug)
			fprintf(stderr, "Best:        %.6f +/- %.6f\n", *offset,
			    *error);

		if (a > b) {
			warnx("Inconsistent times received from NTP server");
			return (-1);
		}

		if (*error <= minerr)
			break;
	}

	return (accepts);
}

/* Send out NTP packet. */
int
write_packet(int fd, struct ntp_data *data, int nver)
{
	u_char	packet[NTP_PACKET_MIN];
	ssize_t	length;

	memset(packet, 0, sizeof(packet));

	packet[0] = ((nver ? nver : NTP_VERSION) << 3) | (NTP_MODE_CLIENT);

	data->xmitck = (u_int64_t)arc4random() << 32 | arc4random();

	/*
	 * Send out a random 64-bit number as our transmit time.  The NTP
	 * server will copy said number into the originate field on the
	 * response that it sends us.  This is totally legal per the SNTP spec.
	 *
	 * The impact of this is two fold: we no longer send out the current
	 * system time for the world to see (which may aid an attacker), and
	 * it gives us a (not very secure) way of knowing that we're not
	 * getting spoofed by an attacker that can't capture our traffic
	 * but can spoof packets from the NTP server we're communicating with.
	 *
	 * No endian concerns here.  Since we're running as a strict
	 * unicast client, we don't have to worry about anyone else finding
	 * the transmit field intelligible.
	 */

	memcpy(packet + NTP_TRANSMIT, &data->xmitck, sizeof (u_int64_t));

	data->originate = gettime();

	length = write(fd, packet, sizeof(packet));

	if (length != sizeof(packet)) {
		warn("Unable to send NTP packet to server");
		return (-1);
	}

	return (0);
}

/*
 * Check the packet and work out the offset and optionally the error.
 * Note that this contains more checking than xntp does. Return 0 for
 * success, 1 for failure. Note that it must not change its arguments
 * if it fails.
 */
int
read_packet(int fd, struct ntp_data *data, double *off, double *error)
{
	u_char	receive[NTP_PACKET_MAX];
	struct	timeval tv;
	double	x, y;
	int	length, r;
	fd_set	*rfds;
	static int nosync = 0;

	rfds = calloc(howmany(fd + 1, NFDBITS), sizeof(fd_mask));
	if (rfds == NULL)
		err(1, "calloc");

	FD_SET(fd, rfds);

retry:
	tv.tv_sec = 0;
	tv.tv_usec = 1000000 * MAX_DELAY / MAX_QUERIES;

	r = select(fd + 1, rfds, NULL, NULL, &tv);

	if (r < 0) {
		if (errno == EINTR)
			goto retry;
		else
			warn("select");

		free(rfds);
		return (r);
	}

	if (r != 1 || !FD_ISSET(fd, rfds)) {
		free(rfds);
		return (1);
	}

	free(rfds);

	length = read(fd, receive, NTP_PACKET_MAX);

	if (length < 0) {
		warn("Unable to receive NTP packet from server");
		return (-1);
	}

	if (length < NTP_PACKET_MIN || length > NTP_PACKET_MAX) {
		warnx("Invalid NTP packet size, packet rejected");
		return (1);
	}

	unpack_ntp(data, receive);

	if (data->recvck != data->xmitck) {
		warnx("Invalid cookie received, packet rejected");
		return (1);
	}

	if (data->version < NTP_VERSION_MIN ||
	    data->version > NTP_VERSION_MAX) {
		warnx("Received NTP version %u, need %u or lower",
		    data->version, NTP_VERSION);
		return (1);
	}

	if (data->mode != NTP_MODE_SERVER) {
		warnx("Invalid NTP server mode, packet rejected");
		return (1);
	}

	if (data->stratum > NTP_STRATUM_MAX) {
		warnx("Invalid stratum received, packet rejected");
		return (1);
	}

	if (data->transmit == 0.0) {
		warnx("Server clock invalid, packet rejected");
		return (1);
	}

	if (!nosync && (data->status == 3)) {
		warnx("Alarm condition - server not synched yet?");
		nosync = 1;
	}

	x = data->receive - data->originate;
	y = data->transmit - data->current;

	*off = (x + y) / 2;
	*error = dabs(x - y);

	x = dabs((data->current - data->originate) / 2);

	if (x > *error)
		*error = x;

	return (0);
}

/*
 * Unpack the essential data from an NTP packet, bypassing struct
 * layout and endian problems.  Note that it ignores fields irrelevant
 * to SNTP.
 */
void
unpack_ntp(struct ntp_data *data, u_char *packet)
{
	int32_t i;
	double d;

	data->current = gettime();

	data->status = (packet[0] >> 6);
	data->version = (packet[0] >> 3) & 0x07;
	data->mode = packet[0] & 0x07;
	data->stratum = packet[1];

	memcpy(&data->refid, packet + 12, 4);
	data->refid = ntohl(data->refid);

	for (i = 0, d = 0.0; i < 8; ++i)
	    d = 256.0*d+packet[NTP_RECEIVE+i];

	data->receive = d / NTP_SCALE;

	for (i = 0, d = 0.0; i < 8; ++i)
	    d = 256.0*d+packet[NTP_TRANSMIT+i];

	data->transmit = d / NTP_SCALE;

	/* See write_packet for why this isn't an endian problem. */
	memcpy(&data->recvck, packet + NTP_ORIGINATE, sizeof (u_int64_t));
}

/*
 * Change offset into current UTC time. This is portable, even if
 * struct timeval uses an unsigned long for tv_sec.
 */
void
create_timeval(double difference, struct timeval *new, struct timeval *adjust)
{
	struct timeval old;
	long n;

	/* Start by converting to timeval format. Note that we have to
	 * cater for negative, unsigned values. */
	if ((n = (long) difference) > difference)
		--n;
	adjust->tv_sec = n;
	adjust->tv_usec = (long) (MILLION_D * (difference-n));
	errno = 0;
	if (gettimeofday(&old, NULL))
		err(1, "Could not get local time of day");
	new->tv_sec = old.tv_sec + adjust->tv_sec;
	new->tv_usec = (n = (long) old.tv_usec + (long) adjust->tv_usec);

	if (n < 0) {
		new->tv_usec += MILLION_L;
		--new->tv_sec;
	} else if (n >= MILLION_L) {
		new->tv_usec -= MILLION_L;
		++new->tv_sec;
	}
}

void
debug_packet(const struct ntp_data *data)
{
	printf("status:      %u\n", data->status);
	printf("version:     %u\n", data->version);
	printf("mode:        %u\n", data->mode);
	printf("stratum:     %u\n", data->stratum);
	printf("reference:   0x%08X (%d.%d.%d.%d)\n",
	    data->refid,
	    data->refid >> 24, (data->refid >> 16) & 0xFF,
	    (data->refid >> 8) & 0xFF, data->refid & 0xFF);
	printf("originate:   %f\n", data->originate);
	printf("receive:     %f\n", data->receive);
	printf("transmit:    %f\n", data->transmit);
	printf("current:     %f\n", data->current);
	printf("xmitck:      0x%0llX\n", data->xmitck);
	printf("recvck:      0x%0llX\n", data->recvck);
	printf("Delay:       %f\n", (data->current - data->originate) -
	    (data->transmit - data->receive));
}

#ifndef SYSKERN_MIRTIME_H
/*
 * Converts a time_t measured in kernel ticks into POSIX time_t
 * using leap second information stored in /etc/localtime or an
 * equivalent indicator (e.g. the TZ environment variable).
 * If the kernel time is already measured POSIXly brok^Wcorrect
 * and a POSIX conformant time zone is set, this is a no-op.
 * Algorithm partially from Dan J. Bernstein.
 */
time_t
timet2posix(time_t kerneltick)
{
	struct tm *tm;
	int64_t day;
	int x, y, sec;

	tm = localtime(&kerneltick);

	/* get the seconds out first */
	sec = tm->tm_sec + 60 * tm->tm_min + 3600 * tm->tm_hour -
	    tm->tm_gmtoff;

	/* pull the year; adjust for year 0 not existing */
	if ((day = tm->tm_year + 1900LL) < 0)
		++day;

	/* split year into y(ear in Gregorian Period) and convenient day */
	y = day % 400;
	day /= 400;
	day *= 146097;
	day -= 678882;
	/* add day of month */
	day += tm->tm_mday;

	/* normalise seconds into days */
	while (sec < 0) {
		--day;
		sec += 86400;
	}
	while (sec > 86400) {
		++day;
		sec -= 86400;
	}

	/* assign x the month and normalise into years */
	x = tm->tm_mon;
	while (x < 0) {
		--y;
		x += 12;
	}
	y += x / 12;
	x %= 12;

	/* calculate x as month since march, adjust year for it */
	if (x < 2) {
		x += 10;
		--y;
	} else
		x -= 2;

	/* add length of month since march by fixed-point arithmetic */
	day += (306 * x + 5) / 10;

	/* normalise 400-year cycles again */
	while (y < 0) {
		day -= 146097;
		y += 400;
	}
	day += 146097 * (y / 400);
	y %= 400;

	/* add by year, 4 years, 100 years, 400 years */
	day += 365 * (y % 4);
	y /= 4;
	day += 1461 * (y % 25);
	day += 36524 * (y / 25);

	/* convert to POSIX timestamp */
	day -= 40587;
	day *= 86400;
	day += sec > 86399 ? 86399 : sec;
	return (day);
}
#endif