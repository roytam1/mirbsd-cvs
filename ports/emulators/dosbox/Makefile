# $MirOS$
# $OpenBSD: Makefile,v 1.9 2007/09/16 00:45:13 merdely Exp $

COMMENT=		x86 with DOS emulator targeted at playing games
DISTNAME=		dosbox-0.72
CATEGORIES=		games x11 emulators
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=dosbox/}
HOMEPAGE=		http://www.dosbox.com/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		graphics/png
LIB_DEPENDS+=		SDL_net::devel/sdl-net \
			SDL_sound::devel/sdl-sound

USE_CXX=		Yes
USE_X11=		Yes
NO_REGRESS=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-alsa-midi \
			--disable-alsatest \
			--enable-dynamic-core \
			--enable-dynamic-x86 \
			--enable-dynrec \
			--enable-fpu \
			--enable-fpu-x86

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/dosbox
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/dosbox/

.include <bsd.port.mk>
