# $MirOS: src/lib/libssl/Makefile.inc,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.if (${MACHINE} == "amd64") || (${MACHINE} == "i386")
CPPFLAGS+=	-DL_ENDIAN
.elif (${MACHINE_ARCH} == "powerpc") || (${MACHINE} == "sparc")
CPPFLAGS+=	-DB_ENDIAN
.else
.BEGIN:
	@echo No endianness defined.
	@exit 1
.endif

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

CFLAGS+= -fno-builtin-pow10

.endif
