# $MirOS: src/lib/libssl/Makefile.inc,v 1.2 2005/03/15 18:51:37 tg Exp $

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.include <bsd.own.mk>

COPTS+=		-fno-builtin-pow10

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

.endif
