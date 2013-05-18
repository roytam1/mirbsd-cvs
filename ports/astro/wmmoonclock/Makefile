# $MirOS: ports/astro/wmmoonclock/Makefile,v 1.6 2008/10/04 19:02:54 tg Exp $
# $OpenBSD: Makefile,v 1.14 2002/09/17 14:46:06 wilfried Exp $

COMMENT=		wm-dockapp; shows the moon phase
DISTNAME=		wmMoonClock-1.27
PKGNAME=		${DISTNAME:L}-0
CATEGORIES=		astro x11 x11/windowmaker
HOMEPAGE=		http://nis-www.lanl.gov/~mgh/WindowMaker/DockApps.shtml

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://nis-www.lanl.gov/~mgh/WindowMaker/

MAKE_ENV=		CC=${_PASS_CC:T:Q}
USE_X11=		Yes
NO_REGRESS=		Yes

WRKSRC=			${WRKDIST}/Src

.include <bsd.port.mk>
