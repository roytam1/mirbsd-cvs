# $MirOS: ports/x11/dclock/Makefile,v 1.3 2005/07/07 21:28:39 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2004/05/18 08:45:33 xsa Exp $
# $FreeBSD: Makefile,v 1.9 1999/08/31 06:52:30 mharo Exp $

COMMENT=			digital clock with optional military time and alarm
CATEGORIES=	x11
DISTNAME=	dclock
PKGNAME=	dclock-4-0
EXTRACT_SUFX=	.shar.Z

MASTER_SITES=	${MASTER_SITE_R5CONTRIB}

PERMIT_PACKAGE_CDROM=	"no license"
PERMIT_PACKAGE_FTP=	"no license"
PERMIT_DISTFILES_CDROM=	"no license"
PERMIT_DISTFILES_FTP=	"no license"

USE_X11=	Yes

WRKDIST=	${WRKDIR}

ALL_TARGET=	dclock

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/dclock ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/dclock.man ${PREFIX}/man/man1/dclock.1

.include <bsd.port.mk>
