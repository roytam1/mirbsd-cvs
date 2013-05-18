# $OpenBSD: Makefile,v 1.6 2004/03/02 22:18:53 naddy Exp $

COMMENT=			breakout game with many levels, powerups, good graphics

DISTNAME=	lbreakout2-2.2.2
PKGNAME=	${DISTNAME}-1
CATEGORIES=	games x11

HOMEPAGE=	http://lgames.sourceforge.net/index.php?action=show_project&project=LBreakout2


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=lgames/}

LIB_DEPENDS=	SDL::devel/sdl \
		SDL_mixer::devel/sdl-mixer
MODULES+=		graphics/png
		
CONFIGURE_STYLE=autoconf

USE_X11=	Yes
USE_CXX=	Yes
USE_GMAKE=	Yes

.include <bsd.port.mk>
