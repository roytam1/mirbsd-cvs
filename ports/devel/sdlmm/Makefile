# $MirOS: ports/devel/sdlmm/Makefile,v 1.3 2006/02/09 09:35:50 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/01/02 18:06:32 espie Exp $

COMMENT=			C++ wrapper for the Simple DirectMedia Layer
VERSION=	0.1.8
DISTNAME=	SDLmm-${VERSION}
PKGNAME=	${DISTNAME:L}-0
CATEGORIES=	devel
HOMEPAGE=	http://sdlmm.sourceforge.net/

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=sdlmm/}

LIB_DEPENDS=	SDL::devel/sdl

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	${CONFIGURE_SHARED}
CONFIGURE_ENV+=	LIBS="${LIBS} -lstdc++ -lm"

.include <bsd.port.mk>
