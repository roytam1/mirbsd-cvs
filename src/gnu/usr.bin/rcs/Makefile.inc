# $MirOS$

.ifndef _MODSRC_GNU_USR_BIN_RCS_MAKEFILE_INC

.PATH: ${.CURDIR}/../man ${.CURDIR}/../src

CFLAGS+=	-W -pedantic -Wno-long-long
CPPFLAGS+=	-I${.CURDIR}/..

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
