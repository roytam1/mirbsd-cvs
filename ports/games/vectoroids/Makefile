# $OpenBSD: Makefile,v 1.3 2002/10/14 10:02:51 pvalchev Exp $

COMMENT=			vector-based, pretty, Asteroids clone

VERSION=	1.1.0
DISTNAME=	vectoroids-${VERSION}
CATEGORIES=	games x11

HOMEPAGE=	http://www.newbreedsoftware.com/vectoroids/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	ftp://ftp.sonic.net/pub/users/nbs/unix/x/vectoroids/

LIB_DEPENDS=	SDL::devel/sdl \
		SDL_mixer::devel/sdl-mixer \
		SDL_image::devel/sdl-image

USE_X11=	Yes
USE_CXX=	Yes
USE_GMAKE=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/vectoroids ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/vectoroids/images
	${INSTALL_DATA} ${WRKSRC}/data/images/* ${PREFIX}/share/vectoroids/images
	${INSTALL_DATA_DIR} ${PREFIX}/share/vectoroids/music
	${INSTALL_DATA} ${WRKSRC}/data/music/* ${PREFIX}/share/vectoroids/music
	${INSTALL_DATA_DIR} ${PREFIX}/share/vectoroids/sounds
	${INSTALL_DATA} ${WRKSRC}/data/sounds/* ${PREFIX}/share/vectoroids/sounds
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/vectoroids
	${INSTALL_DATA} ${WRKSRC}/README.txt ${PREFIX}/share/doc/vectoroids/README

.include <bsd.port.mk>
