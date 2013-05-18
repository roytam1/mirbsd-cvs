# $MirOS: ports/devel/apr/util/Makefile,v 1.5 2008/10/02 18:54:48 bsiegert Exp $

COMMENT=		companion library to APR
VERSION=		0.9.17
DISTNAME=		apr-util-${VERSION}

FLAVOURS=		bsddb
FLAVOUR?=

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		apr::devel/apr/apr
MODULES=		textproc/expat converters/libiconv

.if ${FLAVOUR:L:Mbsddb}
LIB_DEPENDS+=		db.4.2::databases/db
CONFIGURE_ARGS+=	--with-dbm=db42 --with-berkeley-db=${LOCALBASE}
.else
CONFIGURE_ARGS+=	--without-berkeley-db
.endif

CONFIGURE_ARGS+=	--with-iconv=${ICONV_PREFIX}
CONFIGURE_ARGS+=	--with-expat=${EXPAT_PREFIX}
CONFIGURE_ARGS+=	--with-apr=${LOCALBASE}

.include <bsd.port.mk>
