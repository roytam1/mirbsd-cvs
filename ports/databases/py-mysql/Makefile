# $OpenBSD: Makefile,v 1.18 2004/01/29 17:13:37 sturm Exp $

BROKEN=			depends on mysql, which is broken

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			python interface to MySQL

VERSION=	0.9.2
DISTNAME=	MySQL-python-${VERSION}
PKGNAME=	py-mysql-${VERSION}-0
CATEGORIES=	databases

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mysql-python/}

HOMEPAGE=	http://sourceforge.net/projects/mysql-python


# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

MODULES=	lang/python

LIB_DEPENDS=	lib/mysql/mysqlclient.10::databases/mysql

USE_CXX=	Yes
NO_REGRESS=	Yes

DOC_DIR=	${PREFIX}/share/doc/MySQL-python

do-configure:
	@perl -i -pe 's|%%LOCALBASE%%|${LOCALBASE}|g' ${WRKSRC}/setup.py

post-install:
	${INSTALL_DATA_DIR} ${DOC_DIR}
	${INSTALL_DATA} ${WRKBUILD}/doc/*.html ${DOC_DIR}


.include <bsd.port.mk>
