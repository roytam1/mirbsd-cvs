# $MirOS$
# $NetBSD: Makefile,v 1.26 2005/04/11 21:45:34 tv Exp $

COMMENT=		Perl module for SDL
V=			1.12
DISTNAME=		SDL-sdlpl-$V
PKGNAME=		p5-SDL-$V-0
CATEGORIES=		devel perl5
HOMEPAGE=		http://sdlperl.org/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sdlpl/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		SDL.:sdl-*-!no_x11:devel/sdl \
			jpeg.62::graphics/jpeg
BUILD_DEPENDS=		::devel/sdl-image \
			::devel/sdl-mixer
RUN_DEPENDS=		${BUILD_DEPENDS}

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
