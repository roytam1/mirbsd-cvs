# $MirOS$
# $OpenBSD: Makefile,v 1.20 2002/12/29 20:41:07 fgsch Exp $

COMMENT=		"GNU's Ubiquitous Intelligent Language for Extension"

VERSION=		1.4
DASH_VER=		p1
DISTNAME=		guile-${VERSION}
PKGNAME=		guile-${VERSION}${DASH_VER}
CATEGORIES=		lang
MASTER_SITES=		${MASTER_SITE_GNU:=guile/}

HOMEPAGE=		http://www.gnu.org/software/guile/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		ltdl::devel/libltdl

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
