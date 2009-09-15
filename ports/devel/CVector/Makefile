# $MirOS: ports/chemistry/openbabel/Makefile,v 1.1 2009/09/15 18:26:22 bsiegert Exp $

COMMENT=		dynamic array API for ANSI C

VERSION=		1.0.3
DISTNAME=		CVector-${VERSION}
CATEGORIES=		devel

HOMEPAGE=		http://cvector.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=cvector/}

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DOCDIR=			${PREFIX}/share/doc/CVector

pre-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}

post-install:
	mkdir -p ${DOCDIR}
	cp ${WRKSRC}/README_CVector.* ${DOCDIR}

.include <bsd.port.mk>
