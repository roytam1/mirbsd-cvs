# $MirOS$
# $OpenBSD: Makefile,v 1.30 2002/11/07 06:37:47 pvalchev Exp $
# $NetBSD: Makefile,v 1.9 1998/04/15 10:38:50 agc Exp $

NOT_FOR_PLATFORM= MirBSD:*:*

COMMENT=	graphical performance meter

DISTNAME=	xosview-1.8.0
DASH_VER=	1
CATEGORIES=	sysutils

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=xosview/}

HOMEPAGE=	http://xosview.sourceforge.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=gnu
MODGNU_RECURSE_DIRS=	${WRKSRC}/config ${WRKSRC}
CONFIGURE_ENV=		UVM=Yes

NO_REGRESS=	Yes

BINGRP=		kmem
BINMODE=	2555

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/xosview ${PREFIX}/bin
	${INSTALL_MAN} ${WRKBUILD}/xosview.1 ${PREFIX}/man/man1
	${INSTALL_DATA} ${WRKBUILD}/Xdefaults \
		${PREFIX}/lib/X11/app-defaults/XOsview

.include <bsd.port.mk>
