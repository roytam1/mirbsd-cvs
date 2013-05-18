# $MirOS: ports/emulators/ines/Makefile,v 1.4 2005/07/07 21:20:45 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2003/04/10 18:08:56 jsyn Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			emulates the Nintendo Entertainment System
PKGNAME=	ines-1.2-1
DISTNAME=	iNES12-Linux-80x86-bin

CATEGORIES=	emulators games
HOMEPAGE=	http://www.komkon.org/fms/iNES/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}
EXTRACT_SUFX=	.tar.Z

RUN_DEPENDS=	:redhat_base-*:emulators/redhat/base

USE_X11=	Yes
NO_BUILD=	Yes
NO_REGRESS=	Yes
WRKDIST=	${WRKDIR}

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ines
	${INSTALL_DATA_DIR} ${PREFIX}/share/ines
	${INSTALL_PROGRAM} ${WRKSRC}/ines ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/iNES.html ${PREFIX}/share/doc/ines
	${INSTALL_DATA} ${WRKSRC}/CART.NES ${PREFIX}/share/ines

.include <bsd.port.mk>
