# $MirOS: ports/devel/guilib/Makefile,v 1.4 2006/02/09 11:11:22 tg Exp $
# $OpenBSD: Makefile,v 1.11 2003/12/30 18:49:04 espie Exp $

COMMENT=			SDL C++ GUI widget library
VER=		1.1.1
PROJ=		GUIlib
DISTNAME=	${PROJ}-${VER}
PKGNAME=	guilib-${VER}-0
CATEGORIES=	devel graphics
MASTER_SITES=	http://www.libsdl.org/projects/${PROJ}/src/
HOMEPAGE=	http://www.libsdl.org/projects/GUIlib/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	SDL.::devel/sdl

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
