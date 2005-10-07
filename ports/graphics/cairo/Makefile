# $MirOS: ports/graphics/cairo/Makefile,v 1.2 2005/09/22 13:55:56 bsiegert Exp $

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
LIB_DEPENDS=		png::graphics/png # \
#			pixman::graphics/libpixman \
#			glitz::graphics/glitz

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV=  	PKG_CONFIG_PATH="${X11BASE}/lib/pkgconfig"

CONFIGURE_ARGS=		--enable-static \
			${CONFIGURE_SHARED}

.include <bsd.own.mk>

.if ${OStype} == "Darwin"
#CONFIGURE_ARGS+=	--disable-freetype
.endif

.include <bsd.port.mk>
