# $MirOS$
# $OpenBSD: Makefile,v 1.15 2003/10/08 17:13:18 sturm Exp $

COMMENT=	minimal window manager

DISTNAME=	wmx-6
CATEGORIES=	x11

HOMEPAGE=	http://www.all-day-breakfast.com/wmx/
MASTER_SITES=	${HOMEPAGE}


PERMIT_PACKAGE_CDROM=	"no license"
PERMIT_PACKAGE_FTP=	"no license"
PERMIT_DISTFILES_CDROM=	"no license"
PERMIT_DISTFILES_FTP=	"no license"

USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=	gnu

NO_REGRESS=	Yes

do-install:
	@${INSTALL_PROGRAM} ${WRKSRC}/wmx ${PREFIX}/bin
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/wmx
	@${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/wmx

.include <bsd.port.mk>
