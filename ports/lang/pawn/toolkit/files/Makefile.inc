# $MirOS$

.ifndef PORT_MAKEFILE_INC
PORT_MAKEFILE_INC=1

.include <bsd.own.mk>

CPPFLAGS+=	-DHAVE_UNISTD_H -DHAVE_INTTYPES_H -DVT100
.if ${OStype:NInterix:NOpenBSD}
CPPFLAGS+=	-DHAVE_STDINT_H
.endif
CPPFLAGS+=	-I${.CURDIR}/.. -I${.CURDIR}/../../linux

.PATH: ${.CURDIR}/.. ${.CURDIR}/../../linux

NOMAN=		Yes

.endif
