# $MirOS: ports/comms/seyon/Makefile,v 1.4 2007/04/11 17:05:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.17 2002/10/25 11:34:24 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	communication package for X11

DISTNAME=	Seyon-2.14b
PKGNAME=	seyon-2.14b-${DASH_VER}
CATEGORIES=	comms x11

MASTER_SITES=	ftp://sipb.mit.edu/pub/seyon/
EXTRACT_SUFX=	-tar.Z

# License: BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=imake
USE_X11=	Yes

WRKDIST=	${WRKDIR}/seyon

NO_REGRESS=	Yes

.include <bsd.port.mk>
