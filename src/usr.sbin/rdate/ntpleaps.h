/**	$MirOS: src/share/misc/licence.template,v 1.7 2006/04/09 22:08:49 tg Rel $ */
/*	$OpenBSD: ntpleaps.h,v 1.3 2004/05/05 20:29:54 jakob Exp $	*/

/*-
 * Copyright (c) 2002, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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

/* Leap second support for SNTP clients
 * This header file and its corresponding C file provide generic
 * ability for NTP or SNTP clients to correctly handle leap seconds
 * by reading them from an always existing file and subtracting the
 * leap seconds from the NTP return value before setting the posix
 * clock. This is fairly portable between operating systems and may
 * be used for patching other ntp clients, too. The tzfile used is:
 * /usr/share/zoneinfo/right/UTC which is available on any unix-like
 * platform with the Olson tz library, which is necessary to get real
 * leap second zoneinfo files and userland support anyways.
 */

#ifndef	_NTPLEAPS_H
#define	_NTPLEAPS_H

/* Offset between struct timeval.tv_sec and a tai64_t */
#define	NTPLEAPS_OFFSET	(4611686018427387914ULL)

/* Hide this ugly value from programmes */
#define	SEC_TO_TAI64(s)	(NTPLEAPS_OFFSET + (u_int64_t)(s))
#define	TAI64_TO_SEC(t)	((t) - NTPLEAPS_OFFSET)

/* Initialises the leap second table. Does not need to be called
 * before usage of the subtract funtion, but calls ntpleaps_read.
 * Returns 0 on success, -1 on error (displays a warning on stderr)
 */
int ntpleaps_init(void);

/* Re-reads the leap second table, thus consuming quite much time.
 * Ought to be called from within daemons at least once a month to
 * ensure the in-memory table is always up-to-date.
 * Returns 0 on success, -1 on error (leap seconds will not be available)
 */
int ntpleaps_read(void);

/* Subtracts leap seconds from the given value (converts NTP time
 * to posix clock tick time.
 * Returns 0 on success, -1 on error (time is unchanged), 1 on leap second
 */
int ntpleaps_sub(u_int64_t *);

/* This macro is not implemented on all operating systems */
#ifndef	SA_LEN
#define	SA_LEN(x)	(((x)->sa_family == AF_INET6) ? \
			    sizeof(struct sockaddr_in6) : \
			    (((x)->sa_family == AF_INET) ? \
				sizeof(struct sockaddr_in) : \
				sizeof(struct sockaddr)))
#endif

#endif
