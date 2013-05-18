# $OpenBSD: Makefile,v 1.11 2004/01/29 17:13:37 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			fast array facility to the Python language

VERSION=	23.1
DISTNAME=	Numeric-${VERSION}
PKGNAME=	py-${DISTNAME}-0
CATEGORIES=	math


# Python License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=numpy/}
HOMEPAGE=	http://www.pfdubois.com/numpy/

MODULES=	lang/python

do-regress:
	cd ${WRKSRC}/Test && ${MODPY_BIN} -i test.py

.include <bsd.port.mk>
