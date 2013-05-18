# $MirOS: ports/devel/sdl-mixer/Makefile,v 1.8 2006/03/30 20:20:14 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/09/25 04:17:33 jolan Exp $

COMMENT=			SDL multi-channel audio mixer library
# do not update to 1.2.6
DISTNAME=	SDL_mixer-1.2.5
PKGNAME=	${DISTNAME:L:S/_/-/}-3
CATEGORIES=	devel audio
MASTER_SITES=	${HOMEPAGE}release/
HOMEPAGE=	http://www.libsdl.org/projects/SDL_mixer/

# LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_X11=	Yes
USE_CXX=	Yes

LIB_DEPENDS=	SDL::devel/sdl \
		smpeg::devel/smpeg \
	 	vorbis.0,vorbisfile.1::audio/libvorbis

CONFIGURE_STYLE=autoconf no-autoheader
CONFIGURE_ARGS+=${CONFIGURE_SHARED}

post-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/.libs/play{mus,wave} ${PREFIX}/bin

.include <bsd.port.mk>
