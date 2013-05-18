# $MirOS: src/gnu/usr.bin/rcs/Makefile.inc,v 1.6 2007/08/24 14:20:02 tg Exp $

.ifndef _MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC

.PATH: ${.CURDIR}/../man ${.CURDIR}/../src

.include <bsd.own.mk>
COPTS+=		-Wall -Wextra -std=gnu99
CPPFLAGS+=	-I${.CURDIR}/.. -DIN_RCS

.if !defined(LIB)
LIBDIR!=	cd ${.CURDIR}/../lib; ${MAKE} ___DISPLAY_MAKEVARS=.OBJDIR
LDADD+=		-L${LIBDIR} -lrcs
DPADD+=		${LIBDIR}/librcs.a
.endif

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

CVSLIB=	${.CURDIR}/../../cvs/lib

_MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC=1
.endif
