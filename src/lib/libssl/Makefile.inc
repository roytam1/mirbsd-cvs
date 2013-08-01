# $MirOS: src/lib/libssl/Makefile.inc,v 1.7 2006/10/15 00:53:04 tg Exp $

.if !defined(_MODSRC_LIB_LIBSSL_MAKEFILE_INC)
_MODSRC_LIB_LIBSSL_MAKEFILE_INC=1

.include <bsd.own.mk>

COPTS+=		-fno-builtin-pow10

.if ${MKC_USAP:L} == "yes"
CPPFLAGS+=	-DOPENSSL_NO_RC5 -DOPENSSL_NO_MDC2
.endif
.if ${NOPIC:L} == "no"
CPPFLAGS+=	-DDSO_DLFCN -DHAVE_DLFCN_H
.endif
CPPFLAGS+=	-DTERMIOS -DANSI_SOURCE -DOPENSSL_NO_ASM -DOPENSSL_NO_KRB5

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

.endif
