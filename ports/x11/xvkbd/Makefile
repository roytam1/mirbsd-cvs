# $MirOS: ports/x11/xvkbd/Makefile,v 1.2 2006/09/14 00:16:04 tg Exp $
# $OpenBSD: Makefile,v 1.2 2002/10/17 20:31:28 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			xvkbd - virtual keyboard for X window system
DISTNAME=		xvkbd-2.6
CATEGORIES=		x11
HOMEPAGE=		http://homepage3.nifty.com/tsato/xvkbd/

# GNU GPLv2 or later
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=		Xaw3d.6::x11/Xaw3d

USE_X11=		Yes
CONFIGURE_STYLE=	imake
NO_REGRESS=		Yes

.include <bsd.port.mk>
