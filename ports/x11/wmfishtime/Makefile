# $MirOS: ports/x11/wmfishtime/Makefile,v 1.4 2008/10/04 19:03:51 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/09/17 15:22:27 wilfried Exp $

COMMENT=			wm-dockapp; clock application with clock, date and fish

DISTNAME=		wmfishtime-1.23
CATEGORIES=     	x11 x11/windowmaker

HOMEPAGE=		http://www.ne.jp/asahi/linux/timecop/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}software/

LIB_DEPENDS=		gtk.1,gdk.1::x11/gtk+1

MAKE_FLAGS=		CC=${_PASS_CC:T:Q} \
			CFLAGS="${CFLAGS} -Wall `gtk-config --cflags`" \
			LIBS="`gtk-config --libs`"

USE_X11=		Yes
NO_REGRESS=		Yes

do-install:
	$(INSTALL_PROGRAM) $(WRKBUILD)/wmfishtime $(PREFIX)/bin
	$(INSTALL_MAN) $(WRKBUILD)/wmfishtime.1 $(PREFIX)/man/man1

.include <bsd.port.mk>
