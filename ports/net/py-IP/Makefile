# $OpenBSD: Makefile,v 1.7 2004/01/25 16:46:30 sturm Exp $

COMMENT=			python module to handle IPv4 and IPv6 address

VERSION=	0.41
DISTNAME=	IPy-${VERSION}
PKGNAME=	py-IP-${VERSION}-0
CATEGORIES=    	net

HOMEPAGE=	http://c0re.23.nu/c0de/IPy/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}

MODULES=	lang/python

MODPY_DISTUTILS_INSTALLARGS=	-O2

do-regress:
	@cd ${WRKSRC}/test; ${MODPY_BIN} ./test_IPy.py

.include <bsd.port.mk>
