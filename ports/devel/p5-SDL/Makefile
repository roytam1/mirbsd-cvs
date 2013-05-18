# $MirOS: ports/devel/p5-SDL/Makefile,v 1.10 2006/11/04 04:25:53 tg Exp $
# $NetBSD: Makefile,v 1.26 2005/04/11 21:45:34 tv Exp $

COMMENT=		Perl module for SDL
V=			1.20.0
DISTNAME=		SDL_perl-$V
PKGNAME=		p5-SDL-$V-2
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

.include <bsd.port.mk>
