# $OpenBSD: Makefile,v 1.7 2003/10/08 17:13:18 sturm Exp $

COMMENT=			time/date applet for WindowMaker

DISTNAME=	wmtime-1.0b2
CATEGORIES=	x11 x11/windowmaker
MASTER_SITES=	ftp://ftp.enteract.com/users/rneswold/
HOMEPAGE=	http://windowmaker.mezaway.org


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

WRKDIST=        ${WRKDIR}/wmtime.app/
WRKSRC=		${WRKDIST}/wmtime/
USE_X11=	Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
