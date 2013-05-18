# $MirOS: ports/devel/sdl-image/Makefile,v 1.6 2006/02/09 11:11:28 tg Exp $
# $OpenBSD: Makefile,v 1.14 2003/05/12 08:23:46 jolan Exp $

COMMENT=			SDL image library
DISTNAME=	SDL_image-1.2.3
PKGNAME=	${DISTNAME:L:S/_/-/}-0
CATEGORIES=	devel graphics
MASTER_SITES=	http://www.libsdl.org/projects/SDL_image/release/
HOMEPAGE=	http://www.libsdl.org/projects/SDL_image/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	SDL.::devel/sdl \
		tiff.35::graphics/tiff \
		jpeg.62.::graphics/jpeg
MODULES+=		graphics/png

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
