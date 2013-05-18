# $MirOS: ports/games/frozen-bubble/Makefile,v 1.3 2006/09/14 00:09:25 tg Exp $
# $NetBSD: Makefile,v 1.16 2005/05/22 20:08:01 jlam Exp $

COMMENT=		Pop the frozen bubbles
DISTNAME=		frozen-bubble-2.0.0
CATEGORIES=		games
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.frozen-bubble.org/

PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.frozen-bubble.org/data/

LIB_DEPENDS+=		SDL_Pango::devel/sdl-pango
B_R_DEPENDS+=		:p5-SDL->=1.20.0-1:devel/p5-SDL \
			:sdl-mixer->=1.2.2:devel/sdl-mixer \
			:sdl-pango->=0.1.2-2:devel/sdl-pango
BUILD_DEPENDS+=		${B_R_DEPENDS}
RUN_DEPENDS+=		${B_R_DEPENDS}

USE_GMAKE=		Yes
CONFIGURE_STYLE=	perl
MODPERL_SRC=		${WRKSRC}/c_stuff
EXTRA_XAKE_FLAGS+=	PREFIX=${PREFIX:Q}

post-install:
	cd ${PREFIX}/share; \
	    find frozen-bubble locale -type d | xargs chmod 755; \
	    find frozen-bubble locale -type f | xargs chmod 444; \
	    find frozen-bubble locale | xargs chown ${BINOWN}:${BINGRP}

.include <bsd.port.mk>
