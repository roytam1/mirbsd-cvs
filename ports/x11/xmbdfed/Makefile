# $OpenBSD: Makefile,v 1.15 2004/04/05 21:41:46 naddy Exp $

COMMENT=			Motif tool for editing X11 bitmap fonts

VERSION=	4.7
DISTNAME=	xmbdfed-${VERSION}
PKGNAME=	${DISTNAME}.1-0
CATEGORIES=	x11
HOMEPAGE=	http://crl.nmsu.edu/~mleisher/xmbdfed.html

# BSD/Public Domain
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://crl.nmsu.edu/~mleisher/
EXTRACT_SUFX=	.tar.bz2
PATCHFILES=	xmbdfed-${VERSION}-patch1

USE_X11=	Yes
USE_MOTIF=	any

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/xmbdfed ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/xmbdfed.man ${PREFIX}/man/man1/xmbdfed.1

.include <bsd.port.mk>
