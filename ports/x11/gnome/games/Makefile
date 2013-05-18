# $MirOS: ports/x11/gnome/games/Makefile,v 1.2 2005/07/06 19:21:39 bsiegert Exp $

COMMENT=		"GNOME games"

VERSION=		2.8.3
DASH_VER=		-0
DISTNAME=		gnome-games-${VERSION}${DASH_VER}
CATEGORIES=		x11/gnome games

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

HOMEPAGE=		http://www.gnome.org/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-games/2.8/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:intltool-*:textproc/intltool \
			:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		gsf-1::devel/libgsf \
			croco-0.6.3.0::textproc/libcroco \
			rsvg-2.10.1::x11/gnome/librsvg \
			guile::lang/guile \
			ltdl::devel/libltdl \
			gnomeui-2.200::x11/gnome/libgnomeui

USE_X11=		Yes
USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--sysconfdir=${SYSCONFDIR}/gnome
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-games
CONFIGURE_ARGS+=	--disable-schemas-install
CONFIGURE_ARGS+=	--with-scores-user=root
CONFIGURE_ARGS+=	--with-scores-group=games

post-patch:
	ln -s /usr/bin/true ${WRKDIR}/bin/scrollkeeper-update

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gnome-games
	mv ${WRKINST}${SYSCONFDIR}/gnome/sound/events/* ${PREFIX}/share/examples/gnome-games

.include <bsd.port.mk>
