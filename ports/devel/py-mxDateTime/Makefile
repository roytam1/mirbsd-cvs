# $OpenBSD: Makefile,v 1.13 2004/03/02 07:41:32 ish Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			Date and Time types for Python
VERSION=	2.0.5
DISTNAME=	egenix-mx-base-${VERSION}
PKGNAME=	py-mxDateTime-${VERSION}-0
CATEGORIES=	devel
MASTER_SITES=	http://www.lemburg.com/files/python/
HOMEPAGE=	http://www.lemburg.com/files/python/eGenix-mx-Extensions.html

# eGenix.com Public License Agreement
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

USE_CXX=	Yes
FLAVOURS=	py2.3
FLAVOUR?=	py2.3

.if ${FLAVOUR} == "py2.3"
MODPY_VERSION=	${FLAVOUR:S/py//}
.else
ERRORS+=	"Fatal: Conflicting flavour: ${FLAVOUR}"
.endif

MODULES=	lang/python
NO_REGRESS=	Yes

.include <bsd.port.mk>
