# $MirOS: ports/games/frozen-bubble/Makefile,v 1.2 2005/07/07 21:21:04 bsiegert Exp $
# $NetBSD: Makefile,v 1.16 2005/05/22 20:08:01 jlam Exp $

COMMENT=			Pop the frozen bubbles
DISTNAME=		frozen-bubble-1.0.0
PKGNAME=		${DISTNAME}-0
CATEGORIES=		games
MASTER_SITES=		http://zarb.org/~gc/fb/
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.frozen-bubble.org/

PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS+=		:p5-SDL->=1.19:devel/p5-SDL
RUN_DEPENDS=		${BUILD_DEPENDS}

USE_GMAKE=		Yes
CONFIGURE_STYLE=	perl
MODPERL_SRC=		${WRKSRC}/c_stuff

.include <bsd.port.mk>
