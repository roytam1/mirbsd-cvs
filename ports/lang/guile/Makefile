# $MirOS: ports/lang/guile/Makefile,v 1.2 2005/07/06 19:21:31 bsiegert Exp $
# $OpenBSD: Makefile,v 1.20 2002/12/29 20:41:07 fgsch Exp $

COMMENT=		"GNU's Ubiquitous Intelligent Language for Extension"

VERSION=		1.4
DISTNAME=		guile-${VERSION}
PKGNAME=		guile-${VERSION}-2
CATEGORIES=		lang
MASTER_SITES=		${MASTER_SITE_GNU:=guile/}

HOMEPAGE=		http://www.gnu.org/software/guile/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		ltdl::devel/libtool

SEPARATE_BUILD=		simple
CONFIGURE_STYLE=	autoconf no-autoheader
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/guile-readline
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

post-extract:
	rm -rf ${WRKSRC}/libltdl

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/aclocal
	${INSTALL_DATA} ${WRKSRC}/guile-config/guile.m4 ${PREFIX}/share/aclocal
	${INSTALL_DATA} ${WRKSRC}/qthreads.m4 ${PREFIX}/share/aclocal

.include <bsd.port.mk>
