# $MirOS: src/gnu/usr.bin/rcs/Makefile.inc,v 1.3 2005/03/15 20:15:14 tg Exp $

.ifndef _MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC

.PATH: ${.CURDIR}/../man ${.CURDIR}/../src

.include <bsd.own.mk>
COPTS+=		-Wall -Wextra -pedantic -std=c99 -U__STRICT_ANSI__
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
