# $MirOS: src/lib/libcitrus_iconv/Makefile.inc,v 1.4 2006/09/07 16:35:23 tg Exp $

.ifndef _MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC
_MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC=1

.include <bsd.own.mk>

NBBASE?=	${BSDSRCDIR}/lib/libcitrus_iconv
NBLIBC=		${NBBASE}/libc

# oh my goddess!
CPPFLAGS+=	-D'__UNCONST(a)=((void *)(unsigned long)(const void *)(a))'
.if ${OBJECT_FMT} == "ELF"
CPPFLAGS+=	-D'_C_LABEL_STRING(x)=x'
.elif (${OBJECT_FMT} == "a.out") || (${OBJECT_FMT} == "PE")
CPPFLAGS+=	-D'_C_LABEL_STRING(x)="_"x'
.else
.error Unknown OBJECT_FMT
.endif
CPPFLAGS+=	-D'__uint8_t=uint8_t'
CPPFLAGS+=	-D'wchar_t=uint32_t' -D_GCC_WCHAR_T	# XXX nice hack, eh?

CPPFLAGS+=	-I${NBLIBC}/citrus -I${NBLIBC}/citrus/modules \
		-I${BSDSRCDIR}/lib/libc/include -I${NBLIBC}

CPPFLAGS+=	-D'_PATH_CSMAPPER="/usr/share/i18n/csmapper"' \
		-D'_PATH_ESDB="/usr/share/i18n/esdb"' \
		-D'_PATH_I18NMODULE="/usr/lib/i18n"' \
		-D'_PATH_ICONV="/usr/share/i18n/iconv"' \
		-DI18NMODULE_MAJOR=${major} \
		-DCITRUS -DCITRUS_ICONV -D_I18N_DYNAMIC

.endif
