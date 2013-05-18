# $MirOS: src/sbin/mount_nfs/Makefile,v 1.2 2005/03/06 19:50:21 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/06/22 21:12:00 otto Exp $

PROG=	mount_nfs
SRCS=	mount_nfs.c getmntopts.c
MAN=	mount_nfs.8

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -DNFS -I${MOUNT}
.PATH:	${MOUNT}

.include <bsd.prog.mk>
