# $MirOS: src/usr.bin/oldroff/Makefile.inc,v 1.3 2005/12/07 08:41:18 tg Exp $
# @(#)Makefile.inc	5.1 (Berkeley) 6/25/90

.ifndef _MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC
_MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC=1

.include <bsd.own.mk>
COPTS+=		-O1 -std=gnu89

TMACTABDIR=	${.CURDIR}/../../../share/tmac/tab

CPPFLAGS+=	-I${TMACTABDIR}
.PATH: ${TMACTABDIR}

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
