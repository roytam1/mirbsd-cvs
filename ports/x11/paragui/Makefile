# $MirOS: ports/x11/paragui/Makefile,v 1.4 2007/05/07 19:48:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2004/02/25 02:35:18 naddy Exp $

COMMENT=	cross-platform high-level application framework
VERSION=	0.7.2
DISTNAME=	paragui-${VERSION}
CATEGORIES=	x11 devel
HOMEPAGE=	http://www.bms-austria.com/projects/paragui/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.bms-austria.com/pub/paragui/release/
BUILD_DEPENDS=	:zip-*:archivers/zip
LIB_DEPENDS=	SDL::devel/sdl \
		SDL_ttf::devel/sdl-ttf \
		SDL_image::devel/sdl-image 
USE_X11=	Yes
USE_CXX=	Yes # depends on sdl-ttf and sdl-image, which uses CXX
USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf
MODGNU_RECURSE_DIRS=	${WRKSRC}/test ${WRKSRC}
CONFIGURE_ENV=		LIBS=-pthread

.include <bsd.port.mk>
