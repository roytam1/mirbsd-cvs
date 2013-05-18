# $MirOS: ports/devel/sdl-ttf/Makefile,v 1.6 2006/06/29 17:32:41 tg Exp $
# $OpenBSD: Makefile,v 1.17 2003/05/12 08:23:46 jolan Exp $

COMMENT=			SDL TrueType fonts library
DISTNAME=		SDL_ttf-2.0.7
PKGNAME=		${DISTNAME:L:S/_/-/}-0
CATEGORIES=		devel graphics
MASTER_SITES=		http://www.libsdl.org/projects/SDL_ttf/release/
HOMEPAGE=		http://www.libsdl.org/projects/SDL_ttf/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=		SDL::devel/sdl

USE_X11=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
