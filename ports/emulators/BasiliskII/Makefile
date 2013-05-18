# $MirOS: ports/emulators/BasiliskII/Makefile,v 1.4 2006/09/14 00:09:08 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/12/23 00:03:57 grange Exp $
# $RuOBSD: Makefile,v 1.4 2002/04/29 11:07:18 grange Exp $
# $NetBSD: Makefile,v 1.1.1.1 2001/12/29 00:22:02 abs Exp $

COMMENT=		open source 68k Macintosh emulator
DISTNAME=		BasiliskII_src_31052001
PKGNAME=		BasiliskII-0.9.1-0
CATEGORIES=		emulators
HOMEPAGE=		http://www.uni-mainz.de/~bauec002/B2Main.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://iphcip1.physik.uni-mainz.de/~cbauer/

WRKDIST=		${WRKDIR}/BasiliskII-0.9
WRKSRC=			${WRKDIST}/src/Unix

LIB_DEPENDS=		gtk.1.2,gdk::x11/gtk+1 \
			esd.2::audio/esound

USE_X11=		Yes
USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/BasiliskII
	${INSTALL_DATA} ${WRKDIST}/README ${PREFIX}/share/doc/BasiliskII/

.include <bsd.port.mk>
