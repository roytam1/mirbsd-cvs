# $MirOS$

.ifndef _MODSRC_SBIN_MOUNT_VND_MAKEFILE_INC
_MODSRC_SBIN_MOUNT_VND_MAKEFILE_INC=1

.include <bsd.own.mk>

SRC_PATH?=	${.CURDIR}/..

CPPFLAGS+=	-I${SRC_PATH}
.PATH: ${SRC_PATH}

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
