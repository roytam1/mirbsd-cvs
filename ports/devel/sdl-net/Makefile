# $MirOS: ports/devel/sdl-net/Makefile,v 1.2 2005/07/07 21:20:27 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2003/05/12 08:23:46 jolan Exp $

COMMENT=	"SDL cross-platform networking library"
DISTNAME=	SDL_net-1.2.5
PKGNAME=	${DISTNAME:L:S/_/-/}-0
CATEGORIES=	devel net
MASTER_SITES=	http://www.libsdl.org/projects/SDL_net/release/
HOMEPAGE=	http://www.libsdl.org/projects/SDL_net/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	SDL::devel/sdl

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ENV+=		CPPFLAGS="-I${LOCALBASE}/include" \
			LDFLAGS="${LDFLAGS} -L${X11BASE}/lib"
CONFIGURE_ARGS+=	--disable-gui \
			${CONFIGURE_SHARED}

.include <bsd.port.mk>
