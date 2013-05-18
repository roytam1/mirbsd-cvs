# $MirOS$

.ifndef _MODSRC_USR_BIN_LESS_MAKEFILE_INC
_MODSRC_USR_BIN_LESS_MAKEFILE_INC=1

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

TOP=		${.CURDIR}/..
.PATH: ${TOP}

HELPFILE=	/usr/share/misc/more.help

CPPFLAGS+=	-I${TOP} -DBINDIR=\"${BINDIR}\" -DSYSDIR=\"/etc\" \
		-DHELPFILE=\"${HELPFILE}\"

.endif
