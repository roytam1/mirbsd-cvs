# $MirOS: ports/audio/aumix/Makefile,v 1.5 2006/12/30 23:02:53 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/04/13 18:36:57 naddy Exp $

FLAVOUR?=		no_x11
.if !${FLAVOUR:L:Mno_x11}
BROKEN=			the gtk+2 flavour is currently broken
.endif

COMMENT=		full-screen ncurses or GTK-based audio mixer
DISTNAME=		aumix-2.8
CATEGORIES=		audio
HOMEPAGE=		http://jpj.net/~trevor/aumix.html

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=aumix/} \
			http://jpj.net/~trevor/aumix/ \
			http://jpj.net/~trevor/aumix/old/
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

FLAVOURS=		no_x11 no_curses dummy
FLAVOUR?=

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--enable-own-labels --without-gtk1

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-gtk
.else
LIB_DEPENDS+=		gdk-x11-2.0.0.14,gdk_pixbuf-2.0.0.14,gtk-x11-2.0.0.14::x11/gtk+
USE_X11=		Yes
.endif

.if ${FLAVOUR:L:Mno_curses}
CONFIGURE_ARGS+=	--without-ncurses
.endif

.if ${FLAVOUR:L:Mdummy}
CONFIGURE_ARGS+=	--enable-dummy-mixer
.endif

.include <bsd.port.mk>
