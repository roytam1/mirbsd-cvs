# $MirOS: src/gnu/usr.bin/rcs/Makefile.inc,v 1.2 2005/03/13 15:50:41 tg Exp $

.ifndef _MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC

.PATH: ${.CURDIR}/../man ${.CURDIR}/../src

CFLAGS+=	-Wall -Wextra -pedantic -std=c99 -U__STRICT_ANSI__
CPPFLAGS+=	-I${.CURDIR}/.. -DIN_RCS

.if !defined(LIB)
LIBDIR!=	cd ${.CURDIR}/../lib; ${MAKE} ___DISPLAY_MAKEVARS=.OBJDIR
LDADD+=		-L${LIBDIR} -lrcs
DPADD+=		${LIBDIR}/librcs.a
.endif

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

_MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC=1
.endif
