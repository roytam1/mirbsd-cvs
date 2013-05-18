# $OpenBSD: Makefile,v 1.2 2002/12/29 20:08:46 fgsch Exp $

COMMENT=	"mpeg-1 video player"

VERSION=	0.4.1
DISTNAME=	enjoympeg-${VERSION}
CATEGORIES=	graphics x11

HOMEPAGE=	http://people.freenet.de/for_Ki/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${HOMEPAGE}

LIB_DEPENDS=	smpeg.1.3:smpeg-*:devel/smpeg

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/enjoympeg
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/enjoympeg

.include <bsd.port.mk>
