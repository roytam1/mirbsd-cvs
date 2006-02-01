# $MirOS: src/lib/libcitrus_iconv/Makefile,v 1.2 2006/01/31 19:13:42 tg Exp $

.include <bsd.own.mk>
.include "Makefile.inc"
.include "i18n_module/shlib_version"
SHLIB_VERSION?=	${major}.${minor}

SUBDIR+=	i18n_module
.if make(obj) || make(clean) || make(cleandir)
SUBDIR+=	test
.endif

.PATH: ${NBLIBC}/citrus ${NBLIBC}/citrus/modules ${NBLIBC}/iconv

LIB=		iconv
DPADD+=		${.CURDIR}/iconv.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/iconv.exp
SRCS=		citrus_bcs.c citrus_csmapper.c citrus_db.c \
		citrus_db_hash.c citrus_esdb.c citrus_hash.c \
		citrus_iconv.c citrus_lookup.c citrus_mapper.c \
		citrus_memstream.c citrus_mmap.c citrus_module.c \
		citrus_none.c citrus_stdenc.c iconv.c
MAN=		iconv.3

MLINKS+=	iconv.3 iconv_open.3 \
		iconv.3 iconv_close.3

.include <bsd.lib.mk>
