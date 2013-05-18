# $MirOS: ports/devel/apr/util/Makefile,v 1.1 2006/10/05 21:11:39 bsiegert Exp $

COMMENT=		companion library to APR
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
