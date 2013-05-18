# $MirOS: ports/devel/pango/Makefile,v 1.12 2009/08/15 20:45:19 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2003/09/23 06:12:41 marcm Exp $

COMMENT=		library for layout and rendering of text
VERSION=		1.18.4
DISTNAME=		pango-${VERSION}
CATEGORIES=		devel x11
HOMEPAGE=		http://www.gtk.org

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/pango/${VERSION:R}/}
EXTRACT_SUFX=           .tar.bz2

LIB_DEPENDS+=		glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib
LIB_DEPENDS+=		cairo.2::graphics/cairo
MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_GMAKE=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--without-qt

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/pango; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/pango/* ${PREFIX}/share/examples/pango/

.include <bsd.port.mk>
