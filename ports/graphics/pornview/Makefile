# $OpenBSD: Makefile,v 1.2 2004/01/30 08:39:48 xsa Exp $

COMMENT=	"image viewer/manager"
DISTNAME=	pornview-0.2.0pre1
CATEGORIES=	graphics

HOMEPAGE=	http://pornview.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pornview/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	gdk_pixbuf.2::graphics/gdk-pixbuf
MODULES+=		graphics/png

USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
