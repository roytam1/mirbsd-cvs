# $MirOS$
# $OpenBSD: Makefile,v 1.5 2008/07/09 12:13:45 martynas Exp $

COMMENT=		protocol definition, declaration and adaptation
VERSION=		1.0
REVISION=		2306
DISTNAME=		PyProtocols
PKGNAME=		py-protocols-${VERSION}r${REVISION}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://peak.telecommunity.com/PyProtocols.html

# PSF/ZPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SUNSITE:=distributions/gentoo/distfiles/}
DISTFILES=		PyProtocols-${VERSION}a0dev_r${REVISION}${EXTRACT_SUFX}

MODULES=		lang/python
RUN_DEPENDS=		::devel/py-decoratortools
REGRESS_DEPENDS=	::devel/py-decoratortools

MODPY_SETUPTOOLS=	Yes

# make regress happy after fake
post-install:
	rm -fr ${WRKSRC}/src/PyProtocols.egg-info
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/py-protocols/ref
	${INSTALL_DATA} ${WRKSRC}/docs/ref/*.tex ${PREFIX}/share/doc/py-protocols/ref/
	${INSTALL_DATA} ${WRKSRC}/README.txt ${PREFIX}/share/doc/py-protocols/

.include <bsd.port.mk>
