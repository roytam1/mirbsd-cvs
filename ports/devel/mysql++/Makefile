# $MirOS: ports/devel/mysql++/Makefile,v 1.3 2006/09/14 00:08:27 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/02/04 07:39:18 sturm Exp $

BROKEN=			depends on mysql, which is broken

COMMENT=			C++ API for MySQL
COMMENT-docs=			C++ API for MySQL documentation
VERSION=		1.7.9
DISTNAME=		mysql++-${VERSION}
PKGNAME-docs=		mysql++-docs-${VERSION}-0
CATEGORIES=		devel
HOMEPAGE=		http://www.mysql.com/downloads/api-mysql++.html

# LPGL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.sunet.se/pub/unix/databases/relational/mysql/Downloads/mysql++/ \
			ftp://ftp.mysql.com/mysql++/

MULTI_PACKAGES=		-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} != "-docs"
LIB_DEPENDS=		lib/mysql/mysqlclient.10::databases/mysql
.endif
.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=		*
.endif

NO_REGRESS=		Yes
USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	--includedir=${LOCALBASE}/include/mysql++

post-extract:
	@rm -rf ${WRKSRC}/sqlplusint/.deps

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mysql++/html
	${INSTALL_DATA} ${WRKSRC}/doc/man-html/* ${PREFIX}/share/doc/mysql++/html

.include <bsd.port.mk>
