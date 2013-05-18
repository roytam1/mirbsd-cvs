# $OpenBSD: Makefile,v 1.2 2004/01/29 17:13:37 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Python interface to the OpenSSL library

VERSION=	0.5.1
DISTNAME=	pyOpenSSL-${VERSION}
PKGNAME=	py-openssl-${VERSION}-0
CATEGORIES=    	security devel

HOMEPAGE=	http://www.sourceforge.net/projects/pyopenssl/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pyopenssl/}

MODULES=	lang/python

EXAMPLESDIR=	${PREFIX}/share/examples/py-openssl

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}/simple
	${INSTALL_DATA} ${WRKSRC}/examples/README ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples/*.py ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples/simple/* ${EXAMPLESDIR}/simple

.include <bsd.port.mk>
