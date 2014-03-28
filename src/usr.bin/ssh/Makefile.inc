# $MirOS: src/usr.bin/ssh/Makefile.inc,v 1.14 2013/08/06 17:06:28 tg Exp $
# $OpenBSD: Makefile.inc,v 1.33 2008/11/04 08:22:12 djm Exp $

.ifndef _MODSRC_USR_BIN_SSH_MAKEFILE_INC
_MODSRC_USR_BIN_SSH_MAKEFILE_INC=1

CPPFLAGS+=	-I${.CURDIR}/..

CFLAGS+=	-Wall
CFLAGS+=	-Wpointer-arith
CFLAGS+=	-Wno-uninitialized
CFLAGS+=	-Wstrict-prototypes
CFLAGS+=	-Wmissing-prototypes
CFLAGS+=	-Wunused
CFLAGS+=	-Wsign-compare
CFLAGS+=	-Wbounded
CFLAGS+=	-Wshadow

CDIAGFLAGS+=	-Wno-cast-qual

#DEBUG=-g

#CPPFLAGS+=	-DSMARTCARD
#LDADD+=	-lsectok

.include <bsd.obj.mk>

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -lssh
DPADD+=		${.CURDIR}/../lib/${__objdir}/libssh.a
LD_R_ON=	-L${.CURDIR}/../libroaming_on/${__objdir} -lroaming_on
DP_R_ON=	${.CURDIR}/../libroaming_on/${__objdir}/libroaming_on.a
LD_R_OFF=	-L${.CURDIR}/../libroaming_off/${__objdir} -lroaming_off
DP_R_OFF=	${.CURDIR}/../libroaming_off/${__objdir}/libroaming_off.a
.else
LDADD+=		-L${.CURDIR}/../lib -lssh
DPADD+=		${.CURDIR}/../lib/libssh.a
LD_R_ON=	-L${.CURDIR}/../libroaming_on -lroaming_on
DP_R_ON=	${.CURDIR}/../libroaming_on/libroaming_on.a
LD_R_OFF=	-L${.CURDIR}/../libroaming_off -lroaming_off
DP_R_OFF=	${.CURDIR}/../libroaming_off/libroaming_off.a
.endif

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
