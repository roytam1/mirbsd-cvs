# $MirOS: ports/sysutils/wmcube-gdk/Makefile,v 1.2 2005/03/30 18:13:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2002/09/17 15:22:27 wilfried Exp $

COMMENT=			wm-dockapp; shows rotating 3d-object and CPU load

DISTNAME=		wmcube-gdk-0.98p2
CATEGORIES=		sysutils x11 x11/windowmaker

HOMEPAGE=		http://www.ne.jp/asahi/linux/timecop/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}software/

LIB_DEPENDS=		gtk.1,gdk.1::x11/gtk+1

USE_X11=		Yes
NO_REGRESS=		Yes

MAKE_FILE=		Makefile.OPENBSD

3D_OBJECTS=		${PREFIX}/share/wmcube

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/wmcube ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${3D_OBJECTS}
	${INSTALL_DATA} ${WRKDIST}/3dObjects/* ${3D_OBJECTS}

.include <bsd.port.mk>
