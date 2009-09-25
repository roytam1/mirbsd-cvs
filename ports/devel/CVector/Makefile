# $MirOS: ports/devel/CVector/Makefile,v 1.1 2009/09/15 19:44:09 bsiegert Exp $

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
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/README_CVector.* ${DOCDIR}/

.include <bsd.port.mk>
