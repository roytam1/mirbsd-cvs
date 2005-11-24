# $MirOS: src/usr.bin/oldroff/Makefile.inc,v 1.1.7.1 2005/03/06 16:56:01 tg Exp $
# @(#)Makefile.inc	5.1 (Berkeley) 6/25/90

.ifndef _MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC
_MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC=1

.include <bsd.own.mk>
COPTS+=		-fno-unit-at-a-time

TMACTABDIR=	${.CURDIR}/../../../share/tmac/tab

CPPFLAGS+=	-I${TMACTABDIR}
.PATH: ${TMACTABDIR}

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
