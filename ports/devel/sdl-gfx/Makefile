# $OpenBSD: Makefile,v 1.4 2004/05/23 23:07:40 jolan Exp $

COMMENT=			primitives drawing/other support functions for SDL
DISTNAME=	SDL_gfx-2.0.11
PKGNAME=	${DISTNAME:L:S/_/-/}-0
CATEGORIES=	devel graphics x11
MASTER_SITES=	${HOMEPAGE}

HOMEPAGE=	http://www.ferzkopp.net/~aschiffler/Software/SDL_gfx-2.0/


# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_GMAKE=	Yes
USE_X11=	Yes
USE_CXX=	Yes

LIB_DEPENDS=	SDL::devel/sdl

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=${CONFIGURE_SHARED}

.if ${MACHINE_ARCH} != "i386"
CONFIGURE_ARGS+=--disable-mmx
.endif

.include <bsd.port.mk>
