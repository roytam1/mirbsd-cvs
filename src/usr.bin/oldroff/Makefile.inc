# $MirOS$
# @(#)Makefile.inc	5.1 (Berkeley) 6/25/90

.ifndef _MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC
_MODSRC_USR_BIN_OLDROFF_MAKEFILE_INC=1

TMACTABDIR=	${.CURDIR}/../../../share/tmac/tab

CPPFLAGS+=	-I${TMACTABDIR}
.PATH: ${TMACTABDIR}

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
