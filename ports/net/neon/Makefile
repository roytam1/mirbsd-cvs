# $MirOS: ports/net/neon/Makefile,v 1.4 2006/03/28 15:50:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/05/19 18:03:00 lebel Exp $

COMMENT=			HTTP and WebDAV client library, with C interface

VERSION=		0.24.7
DISTNAME=		neon-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=     	net www devel

HOMEPAGE=		http://www.webdav.org/neon/
MASTER_SITES=		${HOMEPAGE}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		xml2.2:libxml->=2.4.8:textproc/libxml

MODULES=		converters/libiconv devel/pkgconfig
NO_REGRESS=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} --with-ssl --with-xml2

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/neon/macros
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/neon
.for i in README NEWS BUGS TODO THANKS
	${INSTALL_DATA} ${WRKSRC}/$i ${PREFIX}/share/doc/neon
.endfor
	cd ${WRKSRC}/macros && \
		tar cf - . | (cd ${PREFIX}/share/neon/macros; tar xf -)

.include <bsd.port.mk>
