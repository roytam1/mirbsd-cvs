# $MirOS$
# $OpenBSD: Makefile.inc,v 1.29 2004/06/21 18:34:51 avsm Exp $

CPPFLAGS+=	-I${.CURDIR}/..

CFLAGS+=	-Wall
CFLAGS+=	-Wpointer-arith
CFLAGS+=	-Wno-uninitialized
#CFLAGS+=	-Wstrict-prototypes
CFLAGS+=	-Wmissing-prototypes
CFLAGS+=	-Wunused
#CFLAGS+=	-Wsign-compare
CFLAGS+=	-Wbounded
#CFLAGS+=	-Wshadow

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
