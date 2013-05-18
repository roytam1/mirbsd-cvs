# $OpenBSD: Makefile,v 1.8 2004/02/25 02:35:15 naddy Exp $

COMMENT=			burgertime clone for X

DISTNAME=	burgerspace-1.7.0
CATEGORIES=	games

HOMEPAGE=	http://www3.sympatico.ca/sarrazip/dev/burgerspace.html


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://www3.sympatico.ca/sarrazip/dev/

LIB_DEPENDS=	gengameng.4.1::devel/gengameng \
		SDL_mixer::devel/sdl-mixer

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu

.include <bsd.port.mk>
