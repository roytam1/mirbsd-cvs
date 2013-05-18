# $OpenBSD: Makefile,v 1.3 2004/01/29 17:13:37 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			universal unicode codec using iconv for Python

DISTNAME=	iconvcodec-1.1.2
PKGNAME=	py-${DISTNAME}-0
CATEGORIES=	converters

HOMEPAGE=	http://cjkpython.berlios.de/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://download.berlios.de/cjkpython/

MODPY_DISTUTILS_BUILDARGS=	--with-libiconv=${ICONV_PREFIX}

NO_REGRESS=	Yes

MODULES=	lang/python converters/libiconv

.include <bsd.port.mk>
