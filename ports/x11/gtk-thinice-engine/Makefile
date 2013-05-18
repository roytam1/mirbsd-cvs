# $OpenBSD: Makefile,v 1.4 2003/12/09 18:13:32 marcm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=		"simple, clean theme engine for GTK+2"
VERSION=		2.0.2
DISTNAME=		gtk-thinice-engine-${VERSION}
CATEGORIES=		x11
HOMEPAGE=		http://thinice.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=thinice/}

LIB_DEPENDS=		gdk-x11-2.0.0.11,gdk_pixbuf-2.0.0.11,gtk-x11-2.0.0.11::x11/gtk+
MODULES+=		devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE= 	gnu

.include <bsd.port.mk>
