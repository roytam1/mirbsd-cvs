# $MirOS: ports/x11/gnome/libgnomecanvas/Makefile,v 1.6 2006/02/09 11:15:44 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/12/27 18:57:58 sturm Exp $

COMMENT=			graphics library for GNOME

DISTNAME=		libgnomecanvas-2.12.0
PKGNAME=		${DISTNAME}-0
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomecanvas/2.12/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		art_lgpl_2::graphics/libart \
			gdk-x11-2.0.0.3,gdk_pixbuf-2.0.0.3,gtk-x11-2.0.0.3::x11/gtk+ \
			glade-2.0.0.0::devel/libglade \
			pangoft2-1.0.0.0::devel/pango

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 	--disable-gtk-doc

.include <bsd.port.mk>
