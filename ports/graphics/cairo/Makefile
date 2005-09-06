# $MirOS$

COMMENT=		"vector graphics library"

DISTNAME=		cairo-1.0.0
CATEGORIES=		graphics

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

.include <bsd.own.mk>

.if ${OStype} == "Darwin"
#CONFIGURE_ARGS+=	--disable-freetype
.endif

.include <bsd.port.mk>
