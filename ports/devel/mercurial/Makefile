# $MirOS: ports/devel/mercurial/Makefile,v 1.1 2008/04/21 19:20:25 bsiegert Exp $

COMMENT=		fast, lightweight source control management system

VERSION=		1.5
DISTNAME=		mercurial-${VERSION}
CATEGORIES=		devel

HOMEPAGE=		http://mercurial.selenic.com
MASTER_SITES=		http://www.selenic.com/mercurial/release/

# GPL v2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		lang/python
USE_GMAKE=		Yes

MODPY_USE_DISTUTILS=	Yes
REGRESS_TARGET=		tests

.include <bsd.port.mk>
