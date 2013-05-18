# $MirOS: ports/devel/gal/Makefile,v 1.6 2007/04/11 17:06:19 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/10/14 20:26:08 marcm Exp $

COMMENT=		GNOME Application Libs

VERSION=		1.99.10
DASH_VER=		1
DISTNAME=		gal-${VERSION}
PKGNAME=		gal2-${VERSION}-${DASH_VER}
CATEGORIES=    		devel x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gal/1.99/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			gnomeprintui-2-2::x11/gnome/libgnomeprintui

USE_X11=		Yes
USE_CXX=		Yes # multiple dependencies need CXX
USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
SUBST_VARS=		VERSION

.include <bsd.port.mk>
