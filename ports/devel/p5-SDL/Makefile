# $MirOS: ports/devel/p5-SDL/Makefile,v 1.12 2007/04/13 19:27:20 bsiegert Exp $
# $NetBSD: Makefile,v 1.26 2005/04/11 21:45:34 tv Exp $

COMMENT=		Perl module for SDL
VSN=			1.20.0
DASH_VER=		2
DISTNAME=		SDL_perl-${VSN}
PKGNAME=		p5-SDL-${VSN}-${DASH_VER}
CATEGORIES=		devel perl5
HOMEPAGE=		http://sdlperl.org/
MASTER_SITES=		http://zarb.org/~gc/t/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		jpeg.62::graphics/jpeg
LIB_DEPENDS+=		SDL.::devel/sdl
B_R_DEPENDS+=		:sdl-*-!no_x11:devel/sdl
B_R_DEPENDS+=		:sdl->=1.2.9-4:devel/sdl
B_R_DEPENDS+=		::devel/sdl-image \
			::devel/sdl-mixer \
			::devel/sdl-ttf
MODULES+=		graphics/png

CONFIGURE_ENV+=		PREFIX=${PREFIX:Q} \
			CPPFLAGS=${CPPFLAGS:Q}
CONFIGURE_STYLE=	perl

USE_X11=		Yes
USE_CXX=		Yes # depends on SDL, which uses CXX

.include <bsd.port.mk>
