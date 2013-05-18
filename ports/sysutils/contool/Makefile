# $MirOS$
# $OpenBSD: Makefile,v 1.21 2002/10/28 19:53:44 naddy Exp $

COMMENT=	console tool for openlook

DISTNAME=	contool-3.3a
CATEGORIES=	sysutils

MASTER_SITES=	ftp://ftp.kfu.com/pub/


PERMIT_PACKAGE_CDROM=	no fee
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	no fee
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	xview.3,olgx.3::x11/xview/lib
BUILD_DEPENDS=	::x11/xview/config

WRKDIST=	${WRKDIR}
CONFIGURE_STYLE=imake
USE_X11=	Yes

NO_REGRESS=	Yes

pre-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/lib/help

.include <bsd.port.mk>
