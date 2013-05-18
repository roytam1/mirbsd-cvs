# $OpenBSD: Makefile,v 1.25 2004/02/26 23:12:31 brad Exp $

COMMENT=			game where you deal drugs on the streets of NY

DISTNAME=	dopewars-1.5.7
PKGNAME=	${DISTNAME}-2
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=dopewars/}

HOMEPAGE=	http://dopewars.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=	devel/gettext devel/pkgconfig
LIB_DEPENDS+=   glib-2.0.0.0::devel/glib

USE_GMAKE=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= --enable-nls \
		 --enable-strict \
		 --disable-esd \
		 --disable-gui-server \
		 --disable-plugins \
		 --disable-sdl

FLAVORS=	no_x11
FLAVOR?=

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+= --disable-gui-client
.else
LIB_DEPENDS+=	gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
		atk-1.0.0.0::devel/atk \
		pango-1.0.0.0,pangox-1.0.0.0,pangoxft-1.0.0.0::devel/pango \
		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/dopewars
	${INSTALL_DATA} ${WRKSRC}/doc/example-cfg \
		${PREFIX}/share/examples/dopewars/dopewars.cfg

.include <bsd.port.mk>
