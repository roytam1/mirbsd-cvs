# $MirOS: ports/databases/py-psycopg/Makefile,v 1.5 2007/04/03 19:10:51 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/02/23 05:06:40 ish Exp $

COMMENT=	PostgreSQL database adapter for Python
VERSION=	1.1.4
DISTNAME=	psycopg-${VERSION}
PKGNAME=	py-psycopg-${VERSION}-${DASH_VER}
CATEGORIES=	databases
MASTER_SITES=	http://initd.org/pub/software/psycopg/
HOMEPAGE=	http://initd.org/software/psycopg

PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	dependency databases/postgresql is not allowed for CDROM
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

USE_CXX=	Yes
USE_X11=	Yes

PYTHON_VER=	2.3
DATETIME_PATH=	${LOCALBASE}/lib/python${PYTHON_VER}/site-packages/mx/DateTime

LIB_DEPENDS+=	pq.2::databases/postgresql
RUN_DEPENDS+=	:python-${PYTHON_VER}*:lang/python/${PYTHON_VER} \
		:py-mxDateTime->=2.0.0-py${PYTHON_VER}:devel/py-mxDateTime,py${PYTHON_VER}
BUILD_DEPENDS+=	${RUN_DEPENDS}

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	--with-python=python${PYTHON_VER}		\
		--with-python-version=${PYTHON_VER}		\
		--with-mxdatetime-includes=${DATETIME_PATH}/mxDateTime

SUBST_VARS=	PYTHON_VER

NO_REGRESS=	Yes

pre-install:
	mkdir -p ${PREFIX}/lib/zope/lib/python/Products/
	cp -r ${WRKSRC}/ZPsycopgDA/ ${PREFIX}/lib/zope/lib/python/Products/

.include <bsd.port.mk>
