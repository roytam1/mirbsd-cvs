# $MirOS: ports/print/ghostscript/fonts-std/Makefile,v 1.6 2008/05/17 15:32:54 bsiegert Exp $

COMMENT=		Standard Fonts for Ghostscript
VERSION=		8.11
DISTNAME=		ghostscript-fonts-std-${VERSION}
PKGNAME=		gs-fonts-std-${VERSION}-0
CATEGORIES=		print
HOMEPAGE=		http://www.cs.wisc.edu/~ghost/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/fonts
MASTER_SITES=		${GS_SITES}

NO_REGRESS=		Yes
NO_BUILD=		Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/ghostscript/fonts
	${INSTALL_DATA} ${WRKDIST}/* ${PREFIX}/share/ghostscript/fonts/

.include <bsd.port.mk>
