# $MirOS$

.include <bsd.own.mk>
.include "Makefile.inc"
.include "i18n_module/shlib_version"
SHLIB_VERSION?=	${major}.${minor}

SUBDIR+=	i18n_module/iconv_std

.PATH: ${NBLIBC}/citrus ${NBLIBC}/citrus/modules ${NBLIBC}/iconv

LIB=		citrus_iconv
SRCS=		citrus_bcs.c citrus_csmapper.c citrus_db.c \
		citrus_db_hash.c citrus_esdb.c citrus_hash.c \
		citrus_iconv.c citrus_lookup.c citrus_mapper.c \
		citrus_memstream.c citrus_mmap.c citrus_module.c \
		citrus_none.c citrus_stdenc.c iconv.c
MAN=		iconv.3

MLINKS+=	iconv.3 iconv_open.3 \
		iconv.3 iconv_close.3

CPPFLAGS+=	-I${NBLIBC}/citrus -I${NBLIBC}/citrus/modules \
		-I${BSDSRCDIR}/lib/libc/include -I${NBLIBC}

CPPFLAGS+=	-D'_PATH_CSMAPPER="/usr/share/i18n/csmapper"' \
		-D'_PATH_ESDB="/usr/share/i18n/esdb"' \
		-D'_PATH_ICONV="/usr/share/i18n/iconv"' \
		-DI18NMODULE_MAJOR=${major} \
		-DCITRUS -DCITRUS_ICONV

.include <bsd.lib.mk>
