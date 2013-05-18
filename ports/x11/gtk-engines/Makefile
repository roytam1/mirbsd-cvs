# $MirOS: ports/x11/gtk-engines/Makefile,v 1.8 2007/06/22 20:56:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/12/17 15:18:33 alek Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		collection of theme engines for GTK+2
VERSION=		2.12.2
DISTNAME=		gtk-engines-${VERSION}
CATEGORIES=		x11

HOMEPAGE=		http://www.gnome.org

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gtk-engines/${VERSION:R}/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0:gtk+2->=2.12:x11/gtk+
LIB_DEPENDS+=		pangocairo-1.0.0.0::devel/pango
BUILD_DEPENDS+=		:intltool->=0.31:textproc/intltool
MODULES=		devel/pkgconfig x11/gtk+

USE_X11=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
USE_GMAKE=		Yes

.include <bsd.port.mk>
