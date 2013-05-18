# $MirOS: ports/devel/vte/Makefile,v 1.3 2006/02/09 11:11:29 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/11/24 00:11:04 espie Exp $

COMMENT=			terminal emulatation library
DISTNAME=		vte-0.11.11
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/vte/0.11/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		gdk-x11-2.0.0.8,gdk_pixbuf-2.0.0.8,gtk-x11-2.0.0.8::x11/gtk+
MODULES+=		devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--disable-python

.include <bsd.port.mk>
