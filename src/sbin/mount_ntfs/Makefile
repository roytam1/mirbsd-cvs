# $MirOS: src/sbin/mount_ntfs/Makefile,v 1.2 2005/03/06 19:50:22 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/02/22 05:16:30 deraadt Exp $

PROG=	mount_ntfs
SRCS=	mount_ntfs.c getmntopts.c

MAN=	mount_ntfs.8
MOUNT=	${.CURDIR}/../mount
CPPFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}

.include <bsd.prog.mk>
