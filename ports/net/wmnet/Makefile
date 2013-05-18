# $MirOS: ports/net/wmnet/Makefile,v 1.4 2007/04/13 19:27:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2003/10/30 21:10:43 jolan Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	little X dock.app network monitor

DISTNAME=	wmnet-1.06
DASH_VER=	1
CATEGORIES=	net x11
HOMEPAGE=	http://www.digitalkaos.net/linux/wmnet/
MASTER_SITES=	${HOMEPAGE}download/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= imake
USE_X11=	Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
