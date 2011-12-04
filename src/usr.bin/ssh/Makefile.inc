# $MirOS: src/usr.bin/ssh/Makefile.inc,v 1.3 2005/04/15 16:28:27 tg Exp $
#	$OpenBSD: Makefile.inc,v 1.30 2005/06/17 02:45:19 djm Exp $

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

#DEBUG=-g

#CPPFLAGS+=	-DSMARTCARD
#LDADD+=	-lsectok

.include <bsd.obj.mk>

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=         -L${.CURDIR}/../lib/${__objdir} -lssh
DPADD+=         ${.CURDIR}/../lib/${__objdir}/libssh.a
.else
LDADD+=         -L${.CURDIR}/../lib -lssh
DPADD+=         ${.CURDIR}/../lib/libssh.a
.endif

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
