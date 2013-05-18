# $OpenBSD: Makefile,v 1.12 2004/01/25 16:46:30 sturm Exp $


COMMENT=			unit testing framework for python

VERSION=		1.4.1
DISTNAME=		pyunit-${VERSION}
PKGNAME=		py-unit-${VERSION}-0
CATEGORIES=     	devel

HOMEPAGE=		http://pyunit.sourceforge.net/


# Python License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=pyunit/}

FLAVORS=		no_x11
FLAVOR?=

USE_CXX=	Yes

MODULES=	lang/python

.if !${FLAVOR:L:Mno_x11}
BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	:python-tkinter-${MODPY_VERSION}*:lang/python/${MODPY_VERSION},-tkinter
.endif

NO_REGRESS=	Yes

.include <bsd.port.mk>
