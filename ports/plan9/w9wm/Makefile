# $MirOS: ports/plan9/w9wm/Makefile,v 1.3 2006/04/25 19:52:24 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2004/02/25 03:49:29 naddy Exp $

COMMENT=			hacked 9wm with support for virtual screens

VERSION=		0.4.2
DASH_VER=		-0
DISTNAME=		w9wm-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
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
