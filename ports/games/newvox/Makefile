# $OpenBSD: Makefile,v 1.6 2003/06/18 21:43:40 pvalchev Exp $

COMMENT=			voxel-style landscape rendering fly-by

DISTNAME=	newvox-1.0
CATEGORIES=	games

HOMEPAGE=	http://www.libsdl.org/projects/newvox/

MASTER_SITES=	${HOMEPAGE}/src/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	SDL::devel/sdl

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/newvox
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/newvox

.include <bsd.port.mk>
