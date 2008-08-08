# $MirOS$

.ifndef PORT_COMPILER_MAKEFILE_INC
PORT_COMPILER_MAKEFILE_INC=1

.include "../Makefile.inc"

DPADD+=		${LIBM} ${LIBPTHREAD}
LDADD+=		-lm

CFLAGS+=	-pthread
LDFLAGS+=	-pthread

.endif
