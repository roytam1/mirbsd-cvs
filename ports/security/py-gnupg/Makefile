# $MirOS$
# $OpenBSD: Makefile,v 1.12 2004/02/09 19:15:39 xsa Exp $

COMMENT=	Python module for GnuPG interface

VERSION=	0.3.2
DISTNAME=	GnuPGInterface-${VERSION}
PKGNAME=	py-gnupg-${VERSION}-0
CATEGORIES=    	security devel

HOMEPAGE=	http://py-gnupg.sourceforge.net/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=py-gnupg/}

MODULES=	lang/python

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	:gnupg-*:security/gnupg

NO_REGRESS=	Yes
USE_CXX=	Yes # depends on libusb, which uses CXX

.include <bsd.port.mk>
