# $MirOS: src/sbin/mount_procfs/Makefile,v 1.2 2005/03/06 19:50:24 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/06/22 21:12:00 otto Exp $

PROG=	mount_procfs
SRCS=	mount_procfs.c getmntopts.c
MAN=	mount_procfs.8

MOUNT=	${.CURDIR}/../mount
CPPFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}

.include <bsd.prog.mk>
