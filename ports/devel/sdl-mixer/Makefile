# $MirOS: ports/devel/sdl-mixer/Makefile,v 1.1.7.1 2005/03/18 15:45:28 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/09/25 04:17:33 jolan Exp $

COMMENT=	"SDL multi-channel audio mixer library"
DISTNAME=	SDL_mixer-1.2.5
PKGNAME=	${DISTNAME:L:S/_/-/}p2
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
		smpeg.1::devel/smpeg \
	 	vorbis.0,vorbisfile.1::audio/libvorbis

SEPARATE_BUILD= concurrent
CONFIGURE_STYLE=autoconf no-autoheader
CONFIGURE_ARGS+=${CONFIGURE_SHARED}

post-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/.libs/play{mus,wave} ${PREFIX}/bin

.include <bsd.port.mk>
