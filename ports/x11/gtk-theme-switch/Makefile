# $MirOS: ports/x11/gtk-theme-switch/Makefile,v 1.4 2008/10/04 19:03:47 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/01/14 01:01:19 naddy Exp $

COMMENT=			switch GTK+ themes quickly

DISTNAME=		gtk-theme-switch-1.0.1
CATEGORIES=		x11 graphics

HOMEPAGE=		http://www.muhri.net/nav.php3?node=gts


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.muhri.net/

LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1

MAKE_FLAGS=		CC=${_PASS_CC:T:Q} \
			CFLAGS="${CFLAGS} `gtk-config --cflags`" \
			LIBS="${LIBS} `gtk-config --libs`"

USE_X11=		Yes

NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/switch ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/switch.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
