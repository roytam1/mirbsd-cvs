# $MirOS: ports/devel/apr/util/Makefile,v 1.2 2006/12/20 15:31:21 tg Exp $

COMMENT=		companion library to APR
VERSION=		0.9.15
DISTNAME=		apr-util-${VERSION}

FLAVORS=		bsddb
FLAVOR?=

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		apr::devel/apr/apr
MODULES=		textproc/expat converters/libiconv

.if ${FLAVOR:L:Mbsddb}
LIB_DEPENDS+=		db.4.2::databases/db
CONFIGURE_ARGS+=	--with-dbm=db42 --with-berkeley-db
.else
CONFIGURE_ARGS+=	--without-berkeley-db
.endif

CONFIGURE_ARGS+=	--with-iconv=${ICONV_PREFIX}
CONFIGURE_ARGS+=	--with-expat=${EXPAT_PREFIX}
CONFIGURE_ARGS+=	--with-apr=${LOCALBASE}

.include <bsd.port.mk>
