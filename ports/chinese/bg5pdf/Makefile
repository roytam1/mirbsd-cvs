# $OpenBSD: Makefile,v 1.6 2004/02/12 15:07:07 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			convert Big5 encoded files to PDF

DISTNAME=       bg5pdf-1.0.0
PKGNAME=	zh-${DISTNAME}-0
CATEGORIES=     chinese print

HOMEPAGE=	http://cschin.yydolphin.net/bg5pdf/


PERMIT_DISTFILES_CDROM= No
PERMIT_DISTFILES_FTP=   Yes
PERMIT_PACKAGE_CDROM=   No
PERMIT_PACKAGE_FTP=     Yes

MASTER_SITES=	${HOMEPAGE}

BUILD_DEPENDS=	:python-${PYTHON_VER}*:lang/python/${PYTHON_VER}
RUN_DEPENDS=	${BUILD_DEPENDS} \
		::chinese/taipeifonts
LIB_DEPENDS=	pdf.2::print/pdflib

USE_CXX=	Yes
WRKDIST=	${WRKDIR}/bg5pdf

PYTHON_VER=	2.1
SUBST_VARS=	PYTHON_VER
MAKE_ENV=	PYTHON_VER=${PYTHON_VER}

NO_REGRESS=	Yes

.include <bsd.port.mk>
