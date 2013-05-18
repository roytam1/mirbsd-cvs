# $MirOS: ports/devel/p5-SDL/Makefile,v 1.7 2006/09/14 00:08:43 tg Exp $
# $NetBSD: Makefile,v 1.26 2005/04/11 21:45:34 tv Exp $

COMMENT=		Perl module for SDL
V=			1.20.0
DISTNAME=		SDL_perl-$V
PKGNAME=		p5-SDL-$V-0
CATEGORIES=		devel perl5
HOMEPAGE=		http://sdlperl.org/
MASTER_SITES=		http://zarb.org/~gc/t/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		SDL.:sdl-*-!no_x11:devel/sdl \
			jpeg.62::graphics/jpeg
BR_DEPENDS=		::devel/sdl-image \
			::devel/sdl-mixer \
			::devel/sdl-ttf
BUILD_DEPENDS+=		${BR_DEPENDS}
RUN_DEPENDS+=		${BR_DEPENDS}
MODULES+=		graphics/png

CONFIGURE_ENV+=		PREFIX=${PREFIX:Q} \
			CPPFLAGS=${CPPFLAGS:Q}
CONFIGURE_STYLE=	perl

USE_X11=		Yes

.include <bsd.port.mk>
