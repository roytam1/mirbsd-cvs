# $MirOS: ports/games/frozen-bubble1/Makefile,v 1.1 2006/11/06 19:16:42 tg Exp $
# $NetBSD: Makefile,v 1.16 2005/05/22 20:08:01 jlam Exp $

COMMENT=		Pop the frozen bubbles
DISTNAME=		frozen-bubble-1.0.0
PKGNAME=		${DISTNAME}-1
CATEGORIES=		games
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.frozen-bubble.org/

PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://zarb.org/~gc/fb/

B_R_DEPENDS+=		:p5-SDL->=1.20.0-2:devel/p5-SDL \
			:sdl-mixer->=1.2.2:devel/sdl-mixer

USE_GMAKE=		Yes
CONFIGURE_STYLE=	perl
MODPERL_SRC=		${WRKSRC}/c_stuff
EXTRA_XAKE_FLAGS+=	PREFIX=${PREFIX:Q}

.include <bsd.port.mk>
