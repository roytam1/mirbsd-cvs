#if 0
.if "0" == "1"
#endif
/*-
 * Copyright © 2013, 2014
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * Server side for a MirBSD ⇐⇒ MirBSD low-traffic entropy transfer.
 *
 * The client looks like this (one line):
 *	sudo mksh -T- -c 'sudo -u tg ssh -l tg mbsdserver \
 *	    /path/to/arngb-slrd >/dev/urandom'
 *
 * Tweak traffic by changing the delay, not the data size. Currently,
 * estimate is one MiB per day (including SSH overhead) upstream.
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/sysctl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

__RCSID("$MirOS: contrib/hosted/tg/deb/arngc/arngb-slrd.c,v 1.1 2014/04/01 19:24:47 tg Exp $");

int
main(void)
{
	size_t z;
	int mib[2];
	unsigned char buf[12];
	struct timespec rqt, rmt;

	while (/* CONSTCOND */ 1) {
		/* read 12 bytes of entropy from the kernel */
		mib[0] = CTL_KERN;
		mib[1] = KERN_ARND;
		z = sizeof(buf);
		if (sysctl(mib, 2, buf, &z, NULL, 0) == -1) {
			/* cannot normally happen on MirBSD */
			syslog(LOG_ERR, "arngb-slrd: sysctl(KERN_ARND): %s",
			    strerror(errno));
			break;
		}
		if (z < 2 || z > sizeof(buf)) {
			/* cannot normally happen on MirBSD */
			syslog(LOG_ERR, "arngb-slrd: short read: %zu", z);
			break;
		}
		/* write those bytes to standard output */
		errno = 0;
		if ((size_t)write(STDOUT_FILENO, buf, z) != z) {
			syslog(LOG_ERR,
			    "arngb-slrd: short write: %zu: %s",
			    z, strerror(errno));
			break;
		}
		/* wait a few seconds, then goto start */
		rqt.tv_sec = 20;
		rqt.tv_nsec = 0;
		errno = 0;
		if (nanosleep(&rqt, &rmt) == -1) {
			syslog(LOG_ERR,
			    "arngb-slrd: couldn't sleep: %lld.%ld: %s",
			    (long long)rmt.tv_sec, rmt.tv_nsec,
			    strerror(errno));
			break;
		}
	}

	return (1);
}

#if 0
.endif

PROG=		arngb-slrd
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
