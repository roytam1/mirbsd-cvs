# $MirOS$
# $OpenBSD: Makefile,v 1.7 2004/02/25 02:35:16 naddy Exp $

COMMENT=		Oxyd/Rock'n'Roll clone
DISTNAME=		enigma-0.81
DASH_VER=		1
CATEGORIES=		games x11
HOMEPAGE=		http://www.nongnu.org/enigma/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		http://savannah.nongnu.org/download/enigma/

LIB_DEPENDS+=		SDL_image.1::devel/sdl-image
LIB_DEPENDS+=		SDL_mixer.2::devel/sdl-mixer
#MODULES+=		lang/lua	# nope, brings its own ☹
USE_GMAKE=		Yes
USE_X11=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC} ${WRKSRC}/lib-src/zipios++
CONFIGURE_ENV+=		LIBS=-pthread

.include <bsd.port.mk>
