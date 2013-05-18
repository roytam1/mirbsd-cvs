# $MirOS: ports/devel/gengameng/Makefile,v 1.1.7.1 2005/03/18 15:44:37 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/02/25 02:35:15 naddy Exp $

IGNORE=		"might be broken, used to use Libtool"

COMMENT=			X11 game engine library
VERSION=	4.1
DISTNAME=	gengameng-${VERSION}
CATEGORIES=	devel x11

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://www3.sympatico.ca/sarrazip/dev/

LIB_DEPENDS=	SDL::devel/sdl \
		SDL_image::devel/sdl-image

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

.include <bsd.port.mk>
