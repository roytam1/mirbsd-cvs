# $MirOS: ports/plan9/9wm/Makefile,v 1.7 2008/10/12 13:53:15 tg Exp $
# $OpenBSD: Makefile,v 1.19 2002/10/28 02:13:21 naddy Exp $

BROKEN=			patches do not apply

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	8 1/2-like Window Manager for X11

PKGNAME=	9wm-1.2pre-1
DISTNAME=	pre-9wm-1.2
CATEGORIES=	plan9

HOMEPAGE=	http://unauthorised.org/dhog/9wm.html
MASTER_SITES=	http://unauthorised.org/dhog/9wm/
EXTRACT_SUFX=	.shar.gz

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= imake
USE_X11=	Yes

WRKDIST=	${WRKDIR}

NO_REGRESS=	Yes

.include <bsd.port.mk>
