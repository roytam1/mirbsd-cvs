# $MirOS$
# $OpenBSD: Makefile,v 1.5 2008/05/24 04:17:11 wcmaier Exp $

COMMENT=		high-level Python web framework
MODPY_EGG_VERSION=	1.0-alpha_2
V=			1.0
LNAME=			django
DISTNAME=		Django-${MODPY_EGG_VERSION}
PKGNAME=		py-${LNAME}-${MODPY_EGG_VERSION:S/-/_/g}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.djangoproject.com/

# BSD License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://media.djangoproject.com/releases/${V}/
MODULES+=		lang/python
NO_REGRESS=		Yes
SUBST_VARS+=		V LNAME

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/${LNAME}
	cd ${WRKSRC}/docs && ${INSTALL_DATA} !(_build|man|Makefile) \
	    ${PREFIX}/share/doc/${LNAME}/
	cd ${WRKSRC}/docs/man && ${INSTALL_MAN} *.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>
