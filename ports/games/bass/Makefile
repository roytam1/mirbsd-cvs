# $OpenBSD: Makefile,v 1.4 2004/02/03 05:46:23 jolan Exp $

PKG_ARCH=	*

COMMENT=			Beneath A Steel Sky
DISTNAME=	BASS-CD
PKGNAME=	bass-20060101-0	# Unversioned
DIST_SUBDIR=	bass-20060101
EXTRACT_SUFX=	.zip
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=scummvm/}


# Conditional
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_CXX=	Yes
NO_BUILD=	Yes
NO_REGRESS=	Yes

RUN_DEPENDS=	:scummvm->=0.5.1:games/scummvm

WRKDIST=	${WRKDIR}/sky-cd

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/bass
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bass
	${INSTALL_DATA} ${WRKSRC}/sky.{dnr,dsk} ${PREFIX}/share/bass
	${INSTALL_DATA} ${WRKSRC}/readme.txt ${PREFIX}/share/doc/bass

.include <bsd.port.mk>
