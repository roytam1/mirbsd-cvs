# $MirOS$
# $OpenBSD: Makefile,v 1.7 2008/07/11 22:41:28 martynas Exp $

COMMENT=		Object Relational Manager
MODPY_EGG_VERSION=	0.10.2
DISTNAME=		SQLObject-${MODPY_EGG_VERSION}
PKGNAME=		py-${DISTNAME}-${DASH_VER}
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlobject.org/

# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://cheeseshop.python.org/packages/source/S/SQLObject/

MODULES+=		lang/python
RUN_DEPENDS=		::www/py-formencode
NO_REGRESS=		Yes
MODPY_SETUPTOOLS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/{doc,examples}/py-SQLObject
	${INSTALL_DATA} ${WRKSRC}/docs/*.txt ${PREFIX}/share/doc/py-SQLObject/
	${INSTALL_DATA} ${WRKSRC}/docs/*.py ${PREFIX}/share/examples/py-SQLObject/

.include <bsd.port.mk>
