# $MirOS: ports/biology/py-biopython/Makefile,v 1.5 2007/04/11 17:12:23 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/07 08:57:15 xsa Exp $

BROKEN=			installation fails

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	Python tools for computational molecular biology

DISTNAME=	biopython-1.50
PKGNAME=	py-${DISTNAME:L}-${DASH_VER}
CATEGORIES=	biology

HOMEPAGE=	http://www.biopython.org/

# BSD-like 
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}DIST/

MODULES=	lang/python

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	::devel/py-mxDateTime \
		::math/py-Numeric

REGRESS_DEPENDS=${RUN_DEPENDS}

EXAMPLESDIR=	${PREFIX}/share/examples/py-biopython

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	cd ${WRKSRC}/Tests; tar cf - * | tar xf - -C ${EXAMPLESDIR} 

do-regress: fake
	@cd ${WRKSRC}/Tests && ${MAKE_ENV} \
		PYTHONPATH=${WRKINST}${MODPY_SITEPKG} \
		${MODPY_BIN} ./run_tests.py

.include <bsd.port.mk>
