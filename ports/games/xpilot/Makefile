# $OpenBSD: Makefile,v 1.15 2002/08/19 17:23:34 pvalchev Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			multiplayer 2d space battles game

DISTNAME=	xpilot-4.5.4
CATEGORIES=	games x11

HOMEPAGE=	http://www.xpilot.org/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	ftp://ftp.xpilot.org/pub/xpilot/ \
		ftp://ftp.xpilot.org/pub/xpilot/old \
		${MASTER_SITE_XCONTRIB:=games/multiplayer/}

USE_X11=	Yes
NO_REGRESS=	Yes

CONFIGURE_STYLE= imake

.include <bsd.port.mk>
