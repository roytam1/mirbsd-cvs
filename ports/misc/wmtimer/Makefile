# $MirOS: ports/misc/wmtimer/Makefile,v 1.2 2005/03/30 18:13:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2003/12/19 12:22:41 wilfried Exp $

COMMENT=			wm-dockapp; alarm clock

DISTNAME=		wmtimer-2.9
CATEGORIES=		misc x11 x11/windowmaker

HOMEPAGE=		http://www.darkops.net/wmtimer/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=		gtk.1,gdk.1::x11/gtk+1

USE_X11=		Yes
NO_REGRESS=		Yes

WRKSRC=			${WRKDIST}/wmtimer

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/wmtimer ${PREFIX}/bin

.include <bsd.port.mk>
