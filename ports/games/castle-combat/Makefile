# $OpenBSD: Makefile,v 1.8 2003/05/12 22:39:27 jolan Exp $

COMMENT=	"Rampart arcade game clone for X11" 

VERSION=	0.7.2
DISTNAME=	castle-combat-${VERSION}
CATEGORIES=	games x11

HOMEPAGE=	http://www.linux-games.com/castle-combat/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	SDL::devel/sdl \
		SDL_mixer::devel/sdl-mixer \
		SDL_net::devel/sdl-net
MODULES+=		graphics/png

MASTER_SITES=	http://user.cs.tu-berlin.de/~karlb/castle-combat/

USE_X11= 	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= --with-png

.include <bsd.port.mk>
