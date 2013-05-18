# $MirOS: ports/databases/py-sqlite/Makefile,v 1.4 2005/07/07 21:18:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2004/03/03 02:41:49 djm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			SQLite adapter for Python

VERSION=	0.5.0
DISTNAME=	pysqlite-${VERSION}
PKGNAME=	py-sqlite-${VERSION}-0
CATEGORIES=	databases
WRKDIST=	${WRKDIR}/pysqlite

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pysqlite/}
HOMEPAGE=	http://pysqlite.sourceforge.net/

# BSD-like
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

LIB_DEPENDS+=	sqlite::databases/sqlite2

MODULES=	lang/python

do-regress: fake
	@cd ${WRKSRC}/test && ${SETENV} PYTHONPATH=${WRKINST}${MODPY_SITEPKG} \
		${MODPY_BIN} ./all_tests.py

.include <bsd.port.mk>

