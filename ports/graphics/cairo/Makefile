# $MirOS: ports/graphics/cairo/Makefile,v 1.12 2008/03/15 20:27:21 bsiegert Exp $

COMMENT=		vector graphics library

DISTNAME=		cairo-1.6.4
DASH_VER=		0
CATEGORIES=		graphics

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

HOMEPAGE=		http://cairographics.org/introduction

# LGPL/MPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://cairographics.org/releases/

#LIB_DEPENDS+=		glitz::graphics/glitz
LIB_DEPENDS+=		pixman-1:pixman->=0.10:graphics/pixman
MODULES+=		devel/pkgconfig
MODULES+=		graphics/png

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--enable-pdf=yes
# enabling those introduces a circular dependency
CONFIGURE_ARGS+=	--enable-svg=no

.include <bsd.port.mk>
