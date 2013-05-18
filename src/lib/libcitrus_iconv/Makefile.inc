# $MirOS: src/lib/libcitrus_iconv/Makefile.inc,v 1.5 2006/11/03 17:14:41 tg Exp $

.ifndef _MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC
_MODSRC_LIB_LIBCITRUS_ICONV_MAKEFILE_INC=1

.include <bsd.own.mk>

NBBASE?=	${BSDSRCDIR}/lib/libcitrus_iconv
NBLIBC=		${NBBASE}/libc

CPPFLAGS+=	-D__NEED_NETBSD_COMPAT			# for the worse...
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
