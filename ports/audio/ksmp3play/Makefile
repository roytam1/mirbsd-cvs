# $OpenBSD: Makefile,v 1.9 2002/12/29 19:29:56 fgsch Exp $

COMMENT=			curses-based mp3 player

DISTNAME=	ksmp3play-0.5.1
CATEGORIES=    	audio

HOMEPAGE=	http://www.xanadunet.net/ksmp3play/index.html


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	SDL::devel/sdl \
		smpeg.1.3:smpeg-*:devel/smpeg

MASTER_SITES=	http://www.xanadunet.net/ksmp3play/

USE_CXX=	Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ENV=	LIBS="-liberty"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ksmp3play
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/ksmp3play

.include <bsd.port.mk>
