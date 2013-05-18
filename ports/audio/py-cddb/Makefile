# $OpenBSD: Makefile,v 1.4 2004/01/30 08:39:48 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			CDDB audio CD track info access in Python
DISTNAME=	CDDB-1.4
PKGNAME=	py-${DISTNAME:L}-0
CATEGORIES=	audio
HOMEPAGE=	http://cddb-py.sourceforge.net/

# GPL 
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=cddb-py/}
# avoid possible conflict with the audio/p5-cddb distfile
DIST_SUBDIR=	${PKGNAME}

MODULES=	lang/python
USE_CXX=	Yes

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/py-cddb
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/py-cddb

.include <bsd.port.mk>
