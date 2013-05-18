# $OpenBSD: Makefile,v 1.4 2003/08/01 13:54:53 sturm Exp $

COMMENT=			python DNS library

VERSION=	2.3.0
DISTNAME=	pydns-${VERSION}
PKGNAME=	py-dns-${VERSION}-0
CATEGORIES=    	net

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pydns/}
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://pydns.sourceforge.net/


# Python License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	lang/python

NO_REGRESS=	Yes

.include <bsd.port.mk>
