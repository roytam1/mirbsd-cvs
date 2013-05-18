# $OpenBSD: Makefile,v 1.2 2002/12/29 20:31:39 fgsch Exp $

COMMENT=			disassembler and other tools for palmos binaries

VERSION=	1.0.2
DISTNAME=	palmpower-${VERSION}
CATEGORIES=	palm


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://www.fh-wilhelmshaven.de/~akcaagaa/palmpower/files/

USE_GMAKE=	Yes
CONFIGURE_STYLE= gnu
CPPFLAGS+=	-Dunix

post-build:
	@cd ${WRKSRC}/utils && ${_PASS_CC:Q} ${CFLAGS} -o splitprc splitprc.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/src/pila/pila ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/pilotdis/pilotdis ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/utils/splitprc ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/man/pilotdis.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/palmpower
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/palmpower
	${INSTALL_DATA} ${WRKSRC}/FAQ ${PREFIX}/share/doc/palmpower

.include <bsd.port.mk>
