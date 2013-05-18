# $MirOS: ports/www/links+/Makefile,v 1.4 2006/02/09 11:15:35 tg Exp $
# $OpenBSD: Makefile,v 1.15 2003/11/17 22:59:32 fgsch Exp $

COMMENT=			graphics and text browser with javascript support
VER=		2.1pre17
DISTNAME=	links-${VER}
PKGNAME=	links+-${VER}-0
CATEGORIES=	www
MASTER_SITES=	${HOMEPAGE}download/
HOMEPAGE=	http://atrey.karlin.mff.cuni.cz/~clock/twibright/links/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=	no_x11
FLAVOR?=

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=--enable-javascript --with-ssl --without-pmshell \
		--without-atheos --without-svgalib --without-gpm \
		--without-fb --without-directfb --without-sdl

.if !${FLAVOR:L:Mno_x11}
LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		tiff.35::graphics/tiff
MODULES+=		graphics/png
USE_X11=	Yes
CONFIGURE_ARGS+=--with-x --enable-graphics \
		--with-libjpeg --with-libtiff
.else
CONFIGURE_ARGS+=--without-x --disable-graphics \
		--without-libjpeg --without-libtiff
.endif

DOCS=		AUTHORS BRAILLE_HOWTO BUGS KEYS NEWS README SITES TODO

pre-configure:
	cd ${WRKSRC}/intl && ${SHELL} synclang

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/links+
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/links+/
	${INSTALL_DATA} ${WRKSRC}/doc/links_cal/* ${PREFIX}/share/links+/

.include <bsd.port.mk>
