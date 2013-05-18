# $MirOS: ports/devel/libwnck/Makefile,v 1.5 2006/09/14 00:08:25 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/12/10 20:34:00 marcm Exp $

COMMENT=		window navigator construction kit

DISTNAME=		libwnck-2.18.2
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libwnck/2.18/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS+=		gdk-x11-2.0.0.10,gdk_pixbuf-2.0.0.10,gtk-x11-2.0.0.10::x11/gtk+
LIB_DEPENDS+=		startup-notification-1::devel/startup-notification
LIB_DEPENDS+=		pangocairo-1.0.0.0::devel/pango

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

.include <bsd.port.mk>
