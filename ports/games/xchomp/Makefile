# $MirOS: ports/games/xchomp/Makefile,v 1.4 2006/09/14 00:09:39 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/05/19 12:19:14 xsa Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			Pac-man-like game under X11
DISTNAME=	xchomp-pl1
PKGNAME=	xchomp-1-0
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_R5CONTRIB}

# License: NONE
PERMIT_PACKAGE_CDROM=	"no license"
PERMIT_PACKAGE_FTP=	"no license"
PERMIT_DISTFILES_CDROM=	"no license"
PERMIT_DISTFILES_FTP=	"no license"

WRKDIST=	${WRKDIR}/xchomp
CONFIGURE_STYLE=imake noman

# Change -DFRAME_DELAY=40000 in patchfile/Imakefile value to adjust
# speed of play depending on X server.

NO_REGRESS=	Yes

.include <bsd.port.mk>
