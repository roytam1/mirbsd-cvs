# $MirOS: src/usr.bin/ssh/Makefile.inc,v 1.6 2007/05/08 21:52:56 tg Exp $
# $OpenBSD: Makefile.inc,v 1.30 2005/06/17 02:45:19 djm Exp $

.ifndef _MODSRC_USR_BIN_SSH_MAKEFILE_INC
_MODSRC_USR_BIN_SSH_MAKEFILE_INC=1

CPPFLAGS+=	-I${.CURDIR}/..
CPPFLAGS+=	-DZCONST=const

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
LDADD+=         -L${.CURDIR}/../lib/${__objdir} -lssh
DPADD+=         ${.CURDIR}/../lib/${__objdir}/libssh.a
.else
LDADD+=         -L${.CURDIR}/../lib -lssh
DPADD+=         ${.CURDIR}/../lib/libssh.a
.endif

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

# make position-independent executables to gain improved
# address space randomisation on re-execution
LDFLAGS+=	-pie

.endif
