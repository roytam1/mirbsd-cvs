# $MirOS: ports/x11/libxklavier/Makefile,v 1.4 2007/07/03 19:54:42 bsiegert Exp $

COMMENT=		sudoku game for the console

VERSION=		1.0.1
DISTNAME=		sudoku-${VERSION}
CATEGORIES=		games

HOMEPAGE=		http://www.laurasia.com.au/sudoku/
MASTER_SITES=		http://www.laurasia.com.au/downloads/
EXTRACT_SUFX=		.tgz

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# Public Domain
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_XAKE_FLAGS=	PREFIX=${LOCALBASE:Q}
NO_REGRESS=		Yes

post-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/sudoku
	${INSTALL_DATA} ${WRKSRC}/template ${PREFIX}/share/sudoku/template

.include <bsd.port.mk>
