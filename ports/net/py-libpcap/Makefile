# $OpenBSD: Makefile,v 1.11 2004/02/18 08:31:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			libpcap bindings for Python

DISTNAME=	pylibpcap-0.3.1
PKGNAME=	${DISTNAME:S/py/py-/}-0
CATEGORIES=	net

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pylibpcap/}

MODULES=	lang/python

BUILD_DEPENDS=	:swig-*:devel/swig

NO_REGRESS=	Yes

EXAMPLESDIR=	${PREFIX}/share/examples/py-libpcap

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples/sniff.py ${EXAMPLESDIR}

.include <bsd.port.mk>
