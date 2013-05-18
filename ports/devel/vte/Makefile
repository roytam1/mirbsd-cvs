# $MirOS: ports/devel/vte/Makefile,v 1.6 2007/06/25 21:37:17 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/11/24 00:11:04 espie Exp $

COMMENT=		terminal emulatation library
DISTNAME=		vte-0.16.6
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/vte/0.16/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		pangocairo-1.0.0.0::devel/pango
LIB_DEPENDS+=		gdk-x11-2.0.0.8,gdk_pixbuf-2.0.0.8,gtk-x11-2.0.0.8::x11/gtk+
MODULES+=		devel/pkgconfig

MODGNU_RECURSE_DIRS=	${WRKSRC}/gnome-pty-helper ${WRKSRC}

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--disable-python

.include <bsd.port.mk>
