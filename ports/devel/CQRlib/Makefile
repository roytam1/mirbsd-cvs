# $MirOS: ports/devel/CVector/Makefile,v 1.1 2009/09/15 19:44:09 bsiegert Exp $

COMMENT=		quaternion rotation API

VERSION=		1.0.3
DISTNAME=		CQRlib-${VERSION}
CATEGORIES=		devel

HOMEPAGE=		http://cqrlib.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=cqrlib/}

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DOCDIR=			${PREFIX}/share/doc/CQRlib

pre-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}

post-install:
	mkdir -p ${DOCDIR}
	cp ${WRKSRC}/README_CQRlib.* ${DOCDIR}

.include <bsd.port.mk>
