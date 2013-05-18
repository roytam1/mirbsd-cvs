# $MirOS: ports/devel/pango/Makefile,v 1.6 2006/02/09 11:11:26 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/09/23 06:12:41 marcm Exp $

COMMENT=			library for layout and rendering of text
DISTNAME=		pango-1.10.0
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel x11
HOMEPAGE=		http://www.gtk.org

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.gtk.org/pub/gtk/v2.8/ \
			${MASTER_SITE_GNOME:=sources/pango/1.10/}
EXTRACT_SUFX=           .tar.bz2

LIB_DEPENDS+=		glib-2.0.0.800,gmodule-2.0.0.800,gobject-2.0.0.800::devel/glib
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
