# $MirOS: ports/x11/paragui/Makefile,v 1.1.7.1 2005/03/18 16:00:49 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/02/25 02:35:18 naddy Exp $

COMMENT=	"cross-platform high-level application framework"
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
USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/test
CONFIGURE_ENV=		LIBS=-pthread

.include <bsd.port.mk>
