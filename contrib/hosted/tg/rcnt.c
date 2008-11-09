#if 0
# $MirOS$
#-
# Copyright (c) 2008
#	Thorsten „mirabilos“ Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# is granted to deal in this work without restriction, including un
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.

PROG=		rcnt
NOMAN=		Yes

.include <bsd.prog.mk>

.if "0" == "1"
#endif

#include <sys/param.h>
#include <sys/ioctl.h>
#include <dev/rndioctl.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <wchar.h>

__RCSID("$MirOS$");

int
main(void)
{
	u_int entcnt;
	int fd;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		err(1, "open");

	if (ioctl(fd, RNDGETENTCNT, &entcnt) == -1)
		err(1, "ioctl");

	close(fd);
	printf("%u\n", entcnt);
	return (0);
}

#if 0
.endif
#endif
