# $MirOS$
# $OpenBSD: Makefile,v 1.9 2004/02/01 10:54:23 wilfried Exp $

COMMENT=		drag and drop library

DISTNAME=		dnd.1.1
PKGNAME=		libdnd-1.1-0
CATEGORIES=		x11 devel


# LPGL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tgz

USE_CXX=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf

WRKDIST=		${WRKDIR}/DND
WRKSRC=			${WRKDIST}/DNDlib

# This regression test wants an X11 display
REGRESS_FLAGS+=         DISPLAY=${DISPLAY} XAUTHORITY=${XAUTHORITY}
REGRESS_IS_INTERACTIVE= Yes

do-regress:
	@cd ${WRKBUILD} && ./dndtest

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libdnd
	${INSTALL_DATA} ${WRKDIST}/DNDdoc/* ${PREFIX}/share/doc/libdnd

.include <bsd.port.mk>
