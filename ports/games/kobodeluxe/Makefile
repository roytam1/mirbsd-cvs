# $OpenBSD: Makefile,v 1.5 2004/05/22 19:54:10 jolan Exp $

COMMENT=			sdl port of xkobo
DISTNAME=	KoboDeluxe-0.4pre8
PKGNAME=	${DISTNAME:L}-0
CATEGORIES=	games x11
MASTER_SITES=	${HOMEPAGE}download/

HOMEPAGE=	http://olofson.net/kobodl/
FLAVOURS=	harder
FLAVOUR?=

.if ${FLAVOUR:L:Mharder}
PATCH_LIST=patch-* extra-hard
.endif

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	SDL_image::devel/sdl-image

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
