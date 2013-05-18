# $MirOS: src/usr.bin/less/Makefile.inc,v 1.1 2005/03/13 18:56:31 tg Exp $

.ifndef _MODSRC_USR_BIN_LESS_MAKEFILE_INC
_MODSRC_USR_BIN_LESS_MAKEFILE_INC=1

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

TOP=		${.CURDIR}/..
.PATH: ${TOP}

HELPFILE=	/usr/share/misc/more.help

CPPFLAGS+=	-I${TOP} -DBINDIR=\"${BINDIR}\" -DSYSDIR=\"/etc\" \
		-DHELPFILE=\"${HELPFILE}\" -DHAVE_UTF8_LOCALE

.endif
