# $MirOS: ports/astro/wmspaceweather/Makefile,v 1.6 2008/10/04 19:02:54 tg Exp $
# $OpenBSD: Makefile,v 1.14 2002/09/17 14:46:06 wilfried Exp $

COMMENT=		wm-dockapp; space weather monitor
DISTNAME=		wmSpaceWeather-1.04
PKGNAME=		${DISTNAME:L}-${DASH_VER}
CATEGORIES=		astro x11 x11/windowmaker
HOMEPAGE=		http://nis-www.lanl.gov/~mgh/WindowMaker/DockApps.shtml

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://nis-www.lanl.gov/~mgh/WindowMaker/

RUN_DEPENDS=		:wget-*:net/wget

MAKE_ENV=		CC=${_PASS_CC:T:Q}
USE_X11=		Yes
NO_REGRESS=		Yes

WRKSRC=			${WRKDIST}/wmSpaceWeather

post-extract:
	@cd ${WRKSRC} && make clean

.include <bsd.port.mk>
