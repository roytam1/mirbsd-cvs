# $MirOS: ports/devel/sdl-sound/Makefile,v 1.5 2007/04/11 17:56:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/03/31 03:49:16 jolan Exp $

COMMENT=		library that handles the decoding of sound file formats
DISTNAME=		SDL_sound-1.0.1
DASH_VER=		1
PKGNAME=		${DISTNAME:L:S/_/-/}-${DASH_VER}
CATEGORIES=		devel audio
MASTER_SITES=		${HOMEPAGE}downloads/
HOMEPAGE=		http://icculus.org/SDL_sound/

# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		physfs.0.0::devel/physfs \
			SDL.2.0::devel/sdl \
			smpeg.1.3::devel/smpeg \
			mikmod.2.4::audio/libmikmod \
			vorbis.2.0,vorbisenc.2.0,vorbisfile.3.0::audio/libvorbis \
			FLAC.5.2::audio/flac \
			speex.2.2::audio/speex

USE_CXX=		Yes # depends on smpeg and flac, which uses CXX
USE_X11=		Yes # depends on SDL, which needs X11

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-modplug

.include <bsd.port.mk>
