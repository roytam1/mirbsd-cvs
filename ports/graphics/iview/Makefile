# $OpenBSD: Makefile,v 1.4 2002/12/29 20:08:46 fgsch Exp $

COMMENT=			image viewer for X

VERSION=	1.4
DISTNAME=	iview-${VERSION}
CATEGORIES=	graphics x11

HOMEPAGE=	http://math.smsu.edu/~erik/software.php?id=63


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://math.smsu.edu/~erik/files/

LIB_DEPENDS=	SDL_image::devel/sdl-image

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= autoconf

.include <bsd.port.mk>
