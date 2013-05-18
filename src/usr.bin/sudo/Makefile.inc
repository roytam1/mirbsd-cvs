# $MirOS: src/usr.bin/sudo/Makefile.inc,v 1.2 2005/03/13 18:33:37 tg Exp $
# $OpenBSD: Makefile.inc,v 1.1 2004/01/15 21:32:03 millert Exp $

.ifndef _MODSRC_USR_BIN_SUDO_MAKEFILE_INC
_MODSRC_USR_BIN_SUDO_MAKEFILE_INC=1

CPPFLAGS+=	-I${.CURDIR}/..
CFLAGS+=	-Wall

.include <bsd.obj.mk>

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=         -L${.CURDIR}/../lib/${__objdir} -lsudo
DPADD+=         ${.CURDIR}/../lib/${__objdir}/libsudo.a
.else
LDADD+=         -L${.CURDIR}/../lib -lsudo
DPADD+=         ${.CURDIR}/../lib/libsudo.a
.endif

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
