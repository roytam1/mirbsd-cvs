# $MirOS: ports/audio/xmms-bonk/Makefile,v 1.5 2008/10/04 19:02:58 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/25 02:35:15 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			XMMS input plugin to play bonk files

VERSION=		0.12
DISTNAME=		bonk-xmms-${VERSION}
PKGNAME=		xmms-bonk-${VERSION}-0
CATEGORIES=		audio


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.proustmedia.de/bonk-xmms/

LIB_DEPENDS=		xmms.3::audio/xmms

MAKE_ENV=		CXX=${_PASS_CXX:T:Q}
ALL_TARGET=

NO_REGRESS=		Yes

USE_CXX=		Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/xmms/Input/
	${INSTALL_DATA} ${WRKBUILD}/libbonk.so ${PREFIX}/lib/xmms/Input/

.include <bsd.port.mk>
