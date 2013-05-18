# $MirOS: src/lib/libssl/Makefile.inc,v 1.4 2006/06/17 22:11:32 tg Exp $

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.include <bsd.own.mk>

COPTS+=		-fno-builtin-pow10

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+=	-DL_ENDIAN
.elif ${MACHINE_ARCH} == "sparc"
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
