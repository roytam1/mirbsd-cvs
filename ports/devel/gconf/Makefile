# $MirOS: ports/devel/gconf/Makefile,v 1.9 2007/06/20 19:57:01 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/12/30 04:30:12 marcm Exp $

COMMENT=		configuration database system for GNOME
VERSION=		2.18.0.1
DASH_VER=		1
DISTNAME=		GConf-${VERSION}
PKGNAME=		gconf2-${VERSION}-${DASH_VER}
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/projects/gconf/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/GConf/2.18/}
EXTRACT_SUFX=           .tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		ORBit-2::devel/ORBit \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
			xml2.2.6::textproc/libxml

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes


DEFAULT_GCONF_SOURCE=	xml:readwrite:/var/db/gconf/gconf.xml.defaults

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-conf

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gconf2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/* ${PREFIX}/share/examples/gconf2; \
	${INSTALL_DATA_DIR} ${PREFIX}/db/gconf/gconf.xml.defaults
	${INSTALL_DATA_DIR} ${PREFIX}/db/gconf/gconf.xml.mandatory

.include <bsd.port.mk>
