# $OpenBSD: Makefile,v 1.3 2002/12/29 20:08:46 fgsch Exp $

COMMENT=			dump frames from mpeg-1 movies

VERSION=	0.6
DISTNAME=	dumpmpeg-${VERSION}
CATEGORIES=	graphics x11

HOMEPAGE=	http://sourceforge.net/projects/dumpmpeg/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=dumpmpeg/}

LIB_DEPENDS=	smpeg.1.3:smpeg-*:devel/smpeg

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu

.include <bsd.port.mk>
