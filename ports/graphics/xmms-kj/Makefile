# $OpenBSD: Makefile,v 1.3 2002/08/15 18:41:36 wcobb Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	"XMMS visualization plugin, to display Kjofol skins"

VERSION=	0.95
DISTNAME=	kint_xmms-${VERSION}
PKGNAME=	xmms-kj-${VERSION}-0
CATEGORIES=	graphics
HOMEPAGE=	http://www.csse.monash.edu.au/~timf/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE} \
		http://mirror.csoft.org/xmms-kj/

MODULES+=		graphics/png
LIB_DEPENDS=	xmms.2::audio/xmms

WRKDIST=	${WRKDIR}/xmms-kj
MAKE_FILE=      makefile
ALL_TARGET=	vislib
NO_REGRESS=	Yes
USE_X11=	Yes

MTREE_FILE=	${FILESDIR}/mtree

do-install:
	${INSTALL_PROGRAM} ${WRKDIST}/libkjofol.so \
	    ${PREFIX}/lib/xmms/Visualization
	${INSTALL_DATA} ${WRKDIST}/default.zip \
	    ${PREFIX}/share/xmms/kjofol

.include <bsd.port.mk>
