# $MirOS: ports/graphics/xpaint/Makefile,v 1.3 2007/04/01 11:43:48 bsiegert Exp $
# $OpenBSD: Makefile,v 1.31 2002/11/22 02:37:37 margarida Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		simple paint program

VERSION=		2.6.2
DISTNAME=		xpaint-${VERSION}
CATEGORIES=		graphics x11

HOMEPAGE=		http://home.worldonline.dk/torsten/xpaint/

MASTER_SITES=		${HOMEPAGE}


# License: BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff \
			png.2::graphics/png

USE_X11=		Yes
CONFIGURE_STYLE= 	imake

WRKDIST=		${WRKDIR}/xpaint

NO_REGRESS=		Yes

.include <bsd.port.mk>
