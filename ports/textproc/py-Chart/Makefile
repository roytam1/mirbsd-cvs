# $OpenBSD: Makefile,v 1.13 2004/02/01 09:31:46 xsa Exp $


COMMENT=			python library for creating postscript or PDF charts

VERSION=	1.35
DISTNAME=	PyChart-${VERSION}
PKGNAME=	py-Chart-${VERSION}-0
CATEGORIES=	textproc devel

HOMEPAGE=	http://www.hpl.hp.com/personal/Yasushi_Saito/pychart/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}

MODULES=	lang/python

RUN_DEPENDS+=	:ghostscript-*:print/ghostscript/artifex

NO_REGRESS=	Yes

DOCSDIR=	${PREFIX}/share/doc/py-Chart
EXAMPLESDIR=	${PREFIX}/share/examples/py-Chart

post-install:
	${INSTALL_DATA_DIR} ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/pychart/* ${DOCSDIR}
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/demos/*.py ${EXAMPLESDIR}

.include <bsd.port.mk>
