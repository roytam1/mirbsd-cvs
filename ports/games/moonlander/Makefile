# $OpenBSD: Makefile,v 1.2 2003/05/12 08:23:47 jolan Exp $

COMMENT=			clone of atari game
DISTNAME=	moon-lander-1.0
PKGNAME=	moonlander-1.0-0
CATEGORIES=	games x11
MASTER_SITES=	http://downloads.daveblood.com/lunar_lander/

HOMEPAGE=	http://magigames.org/moonlander.html


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	SDL_image::devel/sdl-image \
		SDL_mixer::devel/sdl-mixer

NO_REGRESS=	Yes
USE_X11=	Yes
USE_CXX=	Yes

WRKDIST=	${WRKDIR}/moon-lander

FLAVOURS=	no_sound
FLAVOUR?=

.if ${FLAVOUR:L:Mno_sound}
CFLAGS+=	-DNOSOUND
.endif

do-configure:
	perl -pi -e 's,%%PREFIX%%,${PREFIX},g' ${WRKSRC}/moon_lander.c

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/moonlander ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/moonlander
	@cp -R ${WRKSRC}/{fonts,images,sounds} ${PREFIX}/share/moonlander

post-install:
	@find ${PREFIX}/share/moonlander -type f -print0 |xargs -0 chmod 444

.include <bsd.port.mk>
