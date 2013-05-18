# $MirOS: src/sbin/mount_nfs/Makefile,v 1.3 2005/10/18 18:51:43 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/06/22 21:12:00 otto Exp $

PROG=	mount_nfs
SRCS=	mount_nfs.c getmntopts.c
MAN=	mount_nfs.8

MOUNT=	${.CURDIR}/../mount
CPPFLAGS+= -DNFS -I${MOUNT}
.PATH:	${MOUNT}

.include <bsd.prog.mk>
