# $MirOS: ports/www/links+/Makefile,v 1.5 2006/09/14 00:14:40 tg Exp $
# $OpenBSD: Makefile,v 1.15 2003/11/17 22:59:32 fgsch Exp $

COMMENT=		graphics and text browser with javascript support
VER=			2.1pre24
DISTNAME=		links-${VER}
PKGNAME=		links+-${VER}-0
CATEGORIES=		www
MASTER_SITES=		${HOMEPAGE}download/
HOMEPAGE=		http://links.twibright.com/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=		no_x11
FLAVOR?=

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV+=		PKG_CONFIG=no ac_cv_path_PKG_CONFIG=no
CONFIGURE_ENV+=		ac_cv_lib_pcre_pcre_compile=no
CONFIGURE_ARGS+=	--enable-javascript \
			--without-libfl \
			--without-gpm \
			--with-ssl \
			--without-svgalib \
			--without-fb \
			--without-directfb \
			--without-pmshell \
			--without-atheos

.if !${FLAVOR:L:Mno_x11}
USE_X11=		Yes
MODULES+=		graphics/png
LIB_DEPENDS+=		jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
CONFIGURE_ARGS+=	--enable-graphics \
			--with-x \
			--with-libjpeg \
			--with-libtiff
.else
CONFIGURE_ARGS+=	--disable-graphics \
			--without-x \
			--without-libjpeg \
			--without-libtiff
.endif

DOCS=		AUTHORS BRAILLE_HOWTO ChangeLog KEYS Links_logo.png NEWS

# Required if lang files are patched
#pre-configure:
#	cd ${WRKSRC}/intl && ${SHELL} synclang

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/links+
	cd ${WRKSRC}/doc/links_cal && ${INSTALL_DATA} * ${PREFIX}/share/links+/
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/links+/

.include <bsd.port.mk>
