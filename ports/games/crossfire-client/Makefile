# $MirOS: ports/games/crossfire-client/Makefile,v 1.2 2005/03/30 18:13:27 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2003/08/19 09:40:32 espie Exp $

COMMENT=	"graphical networked AD&D style game"

VERSION=	1.4.0
DISTNAME=	crossfire-client-${VERSION}
CATEGORIES=	games x11

IMGDIST=	crossfire-client-images-${VERSION}
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${IMGDIST}${EXTRACT_SUFX}

HOMEPAGE=	http://crossfire.real-time.com/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=crossfire/}

LIB_DEPENDS=   	gtk.1.2,gdk.1.2::x11/gtk+1 \
		SDL.1::devel/sdl \
		SDL_image.1::devel/sdl-image
MODULES+=		graphics/png

CONFIGURE_ARGS=	--disable-gnome	

NO_REGRESS=	Yes

USE_X11=		Yes
USE_CXX=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/utils
CONFIGURE_STYLE=	gnu

IMG=	bmaps.client crossfire.base crossfire.clsc

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/crossfire-client
.for file in ${IMG}
	${INSTALL_DATA} ${WRKDIR}/${file} ${PREFIX}/share/crossfire-client
.endfor

.include <bsd.port.mk>
