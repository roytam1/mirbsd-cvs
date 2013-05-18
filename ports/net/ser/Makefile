# $MirOS: ports/net/ser/Makefile,v 1.6 2008/04/07 19:20:05 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/01/02 04:56:24 brad Exp $

BROKEN=			depends on mysql, which is broken

ONLY_FOR_PLATFORM=	*:*:i386 *:*:sparc

COMMENT=		SIP Express Router
VERSION=		0.8.10
DISTNAME=		ser-${VERSION}_src
PKGNAME=		ser-${VERSION}-${DASH_VER}
CATEGORIES=		net
MASTER_SITES+=		ftp://ftp.berlios.de/pub/ser/${VERSION}/src/
HOMEPAGE=		http://www.iptel.org/ser/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/ser-${VERSION}

USE_GMAKE=		Yes
USE_CXX=		Yes

ALL_TARGET=		all ser.cfg

LIB_DEPENDS=		lib/mysql/mysqlclient.10::databases/mysql
MODULES+=		textproc/expat

do-install:
	cd ${WRKDIST}; ${MAKE_PROGRAM} PREFIX=${WRKINST}${TRUEPREFIX} install

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/ser
	${INSTALL_DATA} ${WRKDIST}/ser.cfg ${PREFIX}/share/examples/ser/

.include <bsd.port.mk>
