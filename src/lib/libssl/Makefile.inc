# $MirOS: src/lib/libssl/Makefile.inc,v 1.14 2014/11/26 21:39:31 tg Exp $

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.include <bsd.own.mk>

.if ${NOPIC:L} == "no"
CPPFLAGS+=	-DDSO_DLFCN -DHAVE_DLFCN_H
.endif
CPPFLAGS+=	-DTERMIOS

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

.endif
