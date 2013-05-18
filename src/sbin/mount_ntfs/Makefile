# $MirOS: src/sbin/mount_ntfs/Makefile,v 1.3 2005/03/15 18:39:19 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/02/22 05:16:30 deraadt Exp $

.if (${MACHINE} == "i386") || (${MACHINE} == "amd64")
PROG=	mount_ntfs
SRCS=	mount_ntfs.c getmntopts.c

MAN=	mount_ntfs.8
MOUNT=	${.CURDIR}/../mount
CPPFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
.else
NOPROG=	Yes
.endif

.include <bsd.prog.mk>
