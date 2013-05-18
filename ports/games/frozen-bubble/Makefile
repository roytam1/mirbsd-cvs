# $MirOS: ports/games/frozen-bubble/Makefile,v 1.9 2006/12/23 03:35:12 tg Exp $
# $NetBSD: Makefile,v 1.16 2005/05/22 20:08:01 jlam Exp $

COMMENT=		Pop the frozen bubbles
DISTNAME=		frozen-bubble-2.1.0
DASH_VER=		1
CATEGORIES=		games
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.frozen-bubble.org/

PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.frozen-bubble.org/data/

LIB_DEPENDS+=		SDL_Pango:sdl-pango->=0.1.2-2:devel/sdl-pango
B_R_DEPENDS+=		:p5-SDL->=1.20.0-2:devel/p5-SDL \
			:sdl-mixer->=1.2.2:devel/sdl-mixer
MODULES+=		devel/pkgconfig
LDFLAGS+=		-Wl,-rpath,${LOCALBASE}/lib

USE_GMAKE=		Yes
CONFIGURE_STYLE=	perl
MODPERL_SRC=		${WRKSRC}/c_stuff
EXTRA_XAKE_FLAGS+=	PREFIX=${PREFIX:Q}
EXTRA_XAKE_FLAGS+=	MANDIR=${PREFIX:Q}/man

post-install:
	cd ${PREFIX}/share; \
	    find frozen-bubble -type d | xargs chmod 755; \
	    find frozen-bubble -type f | xargs chmod 444; \
	    chown -R ${BINOWN}:${BINGRP} frozen-bubble

.include <bsd.port.mk>
