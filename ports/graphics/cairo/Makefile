# $MirOS: ports/graphics/cairo/Makefile,v 1.10 2007/01/06 16:30:18 bsiegert Exp $

COMMENT=		vector graphics library

DISTNAME=		cairo-1.2.6
PKGNAME=		${DISTNAME}-0
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

.include <mirports.sys.mk>

.if ${MACHINE_OS} == "Darwin"
CONFIGURE_ARGS+=	--enable-atsui=yes
.endif

.include <bsd.port.mk>
