# $MirOS: ports/x11/gtk-engines/Makefile,v 1.5 2005/12/29 22:11:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/12/17 15:18:33 alek Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		"collection of theme engines for GTK+2"

DISTNAME=		gtk-engines-2.7.1
CATEGORIES=		x11

HOMEPAGE=		http://www.gnome.org

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gtk-engines/2.7/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		gdk-x11-2.0.0.800,gdk_pixbuf-2.0.0.800,gtk-x11-2.0.0.800::x11/gtk+
MODULES=		devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
