# $MirOS: ports/x11/xforms/Makefile,v 1.2 2006/09/14 00:15:58 tg Exp $
# $OpenBSD: Makefile,v 1.27 2003/05/12 06:48:20 margarida Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			GUI toolkit for X11
DISTNAME=	xforms-1.0
CATEGORIES=	x11
HOMEPAGE=	http://world.std.com/~xforms/
MASTER_SITES=	http://savannah.nongnu.org/download/xforms/stable.pkg/1.0/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE=	imake

BUILD_DEPENDS=		::graphics/jpeg
LIB_DEPENDS=		tiff.35::graphics/tiff
NO_REGRESS=		Yes

.include <bsd.port.mk>
