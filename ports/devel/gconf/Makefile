# $MirOS: ports/devel/gconf/Makefile,v 1.5 2005/12/28 18:31:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/12/30 04:30:12 marcm Exp $

COMMENT=		"configuration database system for GNOME"
VERSION=		2.12.1
DISTNAME=		GConf-${VERSION}
PKGNAME=		gconf2-${VERSION}-0
CATEGORIES=		devel
HOMEPAGE=		http://www.gnome.org/projects/gconf/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/GConf/2.12/}
EXTRACT_SUFX=           .tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		ORBit-2::devel/ORBit \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
			xml2.6::textproc/libxml

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes


DEFAULT_GCONF_SOURCE=	xml::/var/db/gconf/gconf.xml.defaults

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-conf
CONFIGURE_ARGS+=	--enable-gconf-source=${DEFAULT_GCONF_SOURCE}

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gconf2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/* ${PREFIX}/share/examples/gconf2; \

.include <bsd.port.mk>
