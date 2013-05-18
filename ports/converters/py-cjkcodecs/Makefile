# $OpenBSD: Makefile,v 1.4 2004/01/29 17:13:37 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Python unicode codecs for Chinese, Japanese and Korean

DISTNAME=	cjkcodecs-1.0.3
PKGNAME=	py-${DISTNAME}-0
CATEGORIES=	converters

HOMEPAGE=	http://cjkpython.berlios.de/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://download.berlios.de/cjkpython/

NO_REGRESS=	Yes

MODULES=	lang/python

.include <bsd.port.mk>
