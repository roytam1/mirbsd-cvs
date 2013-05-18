# $MirOS: ports/net/xarchie/Makefile,v 1.3 2007/04/13 19:27:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2002/10/28 01:38:46 naddy Exp $
# $FreeBSD: Makefile,v 1.12 1996/12/01 01:23:22 obrien Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	X11 front-end program for the archie network search service

DISTNAME=	xarchie-2.0.10
CATEGORIES=	net

MASTER_SITES=	${MASTER_SITE_XCONTRIB:=applications/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake
USE_X11=		Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
