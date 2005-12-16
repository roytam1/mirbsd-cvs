# $MirOS: ports/graphics/cairo/Makefile,v 1.3 2005/10/07 22:02:59 bsiegert Exp $

COMMENT=		"vector graphics library"

DISTNAME=		cairo-1.0.0
PKGNAME=		${DISTNAME}-2
CATEGORIES=		graphics

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

HOMEPAGE=		http://cairographics.org/introduction

# LGPL/MPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://cairographics.org/releases/

BUILD_DEPENDS+=		:pkgconfig-*:devel/pkgconfig
LIB_DEPENDS+=		png::graphics/png
#LIB_DEPENDS+=		pixman::graphics/libpixman
#LIB_DEPENDS+=		glitz::graphics/glitz

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV=  	PKG_CONFIG_PATH="${X11BASE}/lib/pkgconfig"

CONFIGURE_ARGS=		--enable-static \
			${CONFIGURE_SHARED}

.include <mirports.sys.mk>

.if ${OStype} == "Darwin"
#CONFIGURE_ARGS+=	--disable-freetype
.endif

.include <bsd.port.mk>
