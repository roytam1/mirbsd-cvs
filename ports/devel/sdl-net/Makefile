# $MirOS: ports/devel/sdl-net/Makefile,v 1.5 2006/09/14 00:08:54 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/05/12 08:23:46 jolan Exp $

COMMENT=		SDL cross-platform networking library
DISTNAME=		SDL_net-1.2.7
PKGNAME=		${DISTNAME:L:S/_/-/}-${DASH_VER}
CATEGORIES=		devel net
MASTER_SITES=		http://www.libsdl.org/projects/SDL_net/release/
HOMEPAGE=		http://www.libsdl.org/projects/SDL_net/

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		SDL::devel/sdl

USE_X11=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gui \
			${CONFIGURE_SHARED}

.include <bsd.port.mk>
