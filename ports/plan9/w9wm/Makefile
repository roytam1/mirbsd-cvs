# $MirOS: ports/plan9/w9wm/Makefile,v 1.5 2006/12/20 15:31:37 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/02/25 03:49:29 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		hacked 9wm with support for virtual screens

VERSION=		0.4.2
DISTNAME=		w9wm-${VERSION}
CATEGORIES=		plan9
HOMEPAGE=		http://www.grassouille.org/code/w9wm.en.html

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# see README.9wm
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.grassouille.org/code/w9wm/src/

CONFIGURE_STYLE=	imake
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}/${DISTNAME}.orig

.include <bsd.port.mk>
