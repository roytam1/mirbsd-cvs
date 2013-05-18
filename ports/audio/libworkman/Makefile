# $MirOS: ports/audio/libworkman/Makefile,v 1.4 2007/05/12 22:19:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2002/09/17 14:35:03 wilfried Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		multi-platform CD-Player library

DISTNAME=		libworkman-1999-06-20
DASH_VER=		1
PKGNAME=		libworkman-1.4-${DASH_VER}
CATEGORIES=		audio


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE=	imake

WRKDIST=		${WRKDIR}/libworkman

.include <bsd.port.mk>
