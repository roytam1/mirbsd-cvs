# $MirOS: ports/devel/p5-SDL/Makefile,v 1.6 2006/06/24 17:43:34 bsiegert Exp $
# $NetBSD: Makefile,v 1.26 2005/04/11 21:45:34 tv Exp $

COMMENT=			Perl module for SDL
V=			1.19.2
DISTNAME=		SDL_perl-$V
PKGNAME=		p5-SDL-$V-1
CATEGORIES=		devel perl5
HOMEPAGE=		http://sdlperl.org/
MASTER_SITES=		http://mail.pdaxrom.org/1.1.0beta1/src/
#MASTER_SITES=		http://search.cpan.org/CPAN/authors/id/D/DG/DGOEHRIG/
#MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=SDL_perl/}
#MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sdlpl/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		SDL.:sdl-*-!no_x11:devel/sdl \
			png::graphics/png \
			jpeg.62::graphics/jpeg
BUILD_DEPENDS=		::devel/sdl-image \
			::devel/sdl-mixer \
			::devel/sdl-ttf
RUN_DEPENDS=		${BUILD_DEPENDS}

CONFIGURE_ENV+=		PREFIX=${PREFIX}

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
