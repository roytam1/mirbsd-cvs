# $MirOS: src/lib/libcitrus_iconv/Makefile.inc,v 1.1 2006/01/31 16:43:24 tg Exp $

.ifndef _MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC
_MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC=1

NBBASE?=	${BSDSRCDIR}/lib/libcitrus_iconv
NBLIBC=		${NBBASE}/libc

# oh my goddess!
CPPFLAGS+=	-D'__UNCONST(a)=((void *)(unsigned long)(const void *)(a))'
CPPFLAGS+=	-D'_DIAGASSERT(x)='

.endif
