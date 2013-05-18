# $MirOS$
# $OpenBSD: Makefile,v 1.14 2010/11/20 17:22:45 espie Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		Python interface to the OpenSSL library
MODPY_EGG_VERSION=	0.9
DISTNAME=		pyOpenSSL-${MODPY_EGG_VERSION}
PKGNAME=		py-openssl-${MODPY_EGG_VERSION}-${DASH_VER}
CATEGORIES=    		security devel
HOMEPAGE=		http://www.sourceforge.net/projects/pyopenssl/

# LGPLv2.1
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
