# $MirOS: ports/graphics/cairo/Makefile,v 1.7 2006/09/14 00:09:48 tg Exp $

COMMENT=		vector graphics library

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

LIB_DEPENDS+=		png::graphics/png
#LIB_DEPENDS+=		pixman::graphics/libpixman
#LIB_DEPENDS+=		glitz::graphics/glitz
MODULES+=		devel/pkgconfig

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS=		--enable-static \
			--disable-dependency-tracking \
			--disable-libtool-lock \
			${CONFIGURE_SHARED}

.include <mirports.sys.mk>

.if ${MACHINE_OS} == "Darwin"
#CONFIGURE_ARGS+=	--disable-freetype
.endif

.include <bsd.port.mk>
