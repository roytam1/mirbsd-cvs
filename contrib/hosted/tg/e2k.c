#if 0
.if 0
#endif
/*-
 * Copyright (c) 2009
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
 * Possible return values (mostly or'd):
 * =   1 = argument failure
 * =   2 = read nothing (end of input)
 * =   6 = read nothing (due to error)
 * =   3 = cannot open urandom(4)
 * |   4 = read error
 * |   8 = read less bits than $1 intended, rounded down
 * |  16 = write error, did not try ioctl at all
 * |  32 = ioctl failed
 */

#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/rndioctl.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

#define POOLBYTES 4096
uint8_t buf[POOLBYTES];

int
main(int argc, char *argv[])
{
	ssize_t siz, n;
	u_int ebits;
	int fd, rv = 0;

	if (argc != 2 || !(ebits = (u_int)strtonum(argv[1], 1, POOLBYTES * 8,
	    NULL)))
		errx(1, "Syntax: e2k%s\n\tvalid%s are 1..%u\n",
		    " numbits", " numbits", POOLBYTES * 8);
	siz = 0;
	do {
		if ((n = read(0, buf + siz, POOLBYTES - siz)) == -1) {
			if (errno == EINTR)
				continue;
			/* handle read errors "gracefully" */
			n = 0;
			rv |= 4;
		}
		siz += n;
	} while (n && siz < POOLBYTES);
	if (!siz) {
		if (rv & 4)
			err(6, "read");
		else
			errx(2, "read");
	}
	if (ebits > (size_t)n * 8) {
		ebits = (size_t)n * 8;
		rv |= 8;
	}
	if ((fd = open("/dev/urandom", O_RDWR)) == -1)
		err(3, "open urandom(4)");
	/*
	 * weird, according to OpenBSD RTFM, read(2) can fail with EINTR
	 * but write(2) cannot... we also assume urandom(4) writes quick
	 */
	if (write(fd, buf, siz) != siz) {
		warn("write");
		rv |= 16;
	} else if (ioctl(fd, RNDADDTOENTCNT, &ebits) == -1) {
		warn("ioctl RNDADDTOENTCNT");
		rv |= 32;
	}
	close(fd);
	bzero(buf, sizeof(buf));
	return (rv);
}

#if 0
.endif

PROG=		e2k
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
