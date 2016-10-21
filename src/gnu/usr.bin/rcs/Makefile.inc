# $MirOS: src/gnu/usr.bin/rcs/Makefile.inc,v 1.8 2014/02/09 22:49:29 tg Exp $

.ifndef _MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC

.PATH: ${.CURDIR}/../man ${.CURDIR}/../src

.include <bsd.own.mk>
COPTS+=		-Wall -Wextra
CPPFLAGS+=	-I${.CURDIR}/.. -DIN_RCS

.ifdef LIB
NEED_RCS_LIB?=	No
.endif
NEED_RCS_LIB?=	Yes

.if ${NEED_RCS_LIB:L} == "yes"
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
