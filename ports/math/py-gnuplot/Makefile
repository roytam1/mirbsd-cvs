# $OpenBSD: Makefile,v 1.1.1.1 2004/02/05 23:37:27 xsa Exp $

COMMENT=			Python interface to the gnuplot plotting program

DISTNAME=	gnuplot-py-1.7
PKGNAME=	py-${DISTNAME:S/py-//}-0
CATEGORIES=	math graphics

HOMEPAGE=	http://gnuplot-py.sourceforge.net/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gnuplot-py/}

MODULES=	lang/python

BUILD_DEPENDS+=	:py-Numeric-*:math/py-Numeric
RUN_DEPENDS+=	:py-Numeric-*:math/py-Numeric \
		:gnuplot-*:math/gnuplot

NO_REGRESS=	Yes

DOCSDIR=	${PREFIX}/share/doc/py-gnuplot
EXAMPLESDIR=	${PREFIX}/share/examples/py-gnuplot

post-install:
	${INSTALL_DATA_DIR} ${DOCSDIR}
	cd ${WRKSRC}/doc; tar cf - . | tar xf - -C ${DOCSDIR}
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/test.py ${EXAMPLESDIR}

.include <bsd.port.mk>
