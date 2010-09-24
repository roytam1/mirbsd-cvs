#if 0
# $MirOS: contrib/hosted/tg/rcnt.c,v 1.1 2008/11/09 17:52:48 tg Exp $
#-
# Copyright (c) 2003, 2004, 2005, 2007, 2008, 2010
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

LDSTATIC=	-static
LDFLAGS+=	-nostartfiles -nostdlib
LDADD+=		-lc

.include <bsd.prog.mk>

.if "0" == "1"
#endif

#include <sys/param.h>
#include <sys/ioctl.h>
#include <dev/rndioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: contrib/hosted/tg/rcnt.c,v 1.1 2008/11/09 17:52:48 tg Exp $");

__dead void __start(void);
__dead void _exit__(int);
void out_uint(unsigned int);

const char E1[6] = "rcnt: ";
const char NL = '\n';

void
__start(void)
{
	u_int entcnt;
	int fd, e;
	const char *errcode;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1) {
		e = errno;
		errcode = "open";
		goto errout;
	}

	if (ioctl(fd, RNDGETENTCNT, &entcnt) == -1) {
		e = errno;
		errcode = "ioctl";
		close(fd);
 errout:
		e = e > ELAST ? EPROGMISMATCH : e;
		write(2, E1, 6);
		write(2, errcode, strlen(errcode));
		write(2, E1 + 4, 2);
		write(2, sys_errlist[e], strlen(sys_errlist[e]));
		write(2, &NL, 1);
		_exit__(1);
	}

	close(fd);
	out_uint(entcnt);
	write(1, &NL, 1);
	_exit__(0);
}

__weak_alias(_start, __start);

const char numbers[10] = "0123456789";

void
out_uint(unsigned int i)
{
	if (i > 10)
		out_uint(i / 10);
	write(1, &numbers[i % 10], 1);
}

__asm__(".section .note.miros.ident,\"a\",@progbits"
"\n	.p2align 2"
"\n	.long	2f-1f"			/* name size */
"\n	.long	4f-3f"			/* desc size */
"\n	.long	1"			/* type (OS version note) */
"\n1:	.asciz	\"MirOS BSD\""		/* name */
"\n2:	.p2align 2"
"\n3:	.long	0"			/* desc */
"\n4:	.p2align 2");

#if 0
.endif
#endif
