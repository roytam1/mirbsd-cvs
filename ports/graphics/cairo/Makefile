# $MirOS: ports/graphics/cairo/Makefile,v 1.13 2008/12/07 17:09:27 bsiegert Exp $

COMMENT=		vector graphics library

DISTNAME=		cairo-1.8.8
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

CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--enable-pdf=yes
CONFIGURE_ARGS+=	--enable-svg=yes

pre-patch:
	rm -f ${WRKSRC}/build/lt*

.include <bsd.port.mk>
