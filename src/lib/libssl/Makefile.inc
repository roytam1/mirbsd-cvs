# $MirOS$

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

CFLAGS+= -fno-builtin-pow10

.endif
