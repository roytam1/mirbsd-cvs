# $MirOS: ports/x11/ogle_gui/Makefile,v 1.5 2007/05/07 19:48:16 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2004/04/02 19:07:05 sturm Exp $


COMMENT=			GUI for ogle
DISTNAME=	ogle_gui-0.9.2
HOMEPAGE=	http://www.dtek.chalmers.se/groups/dvd/
# Authors can be reached at dvd@dtek.chalmers.se
MASTER_SITES=	${HOMEPAGE}dist/
CATEGORIES=	x11

CONFIGURE_STYLE=	gnu

# GPL
PERMIT_DISTFILES_CDROM=Yes
PERMIT_DISTFILES_FTP=Yes
PERMIT_PACKAGE_CDROM=Yes
PERMIT_PACKAGE_FTP=Yes

LIB_DEPENDS=	dvdcontrol.9,msgevents.6::x11/ogle \
		xml2::textproc/libxml \
USE_X11=	Yes

FLAVOURS=gtk1
FLAVOUR?=

.if ${FLAVOUR:L} == "gtk1"
LIB_DEPENDS+= 	glade.5.0::devel/libglade0 \
		gtk.1.2::x11/gtk+1
.else
MODULES+=	devel/pkgconfig
LIB_DEPENDS+=	glade-2.0.0.0::devel/libglade \
		gtk-x11-2.0.0.0::x11/gtk+
CONFIGURE_ARGS+=--enable-gtk2
.endif

MODULES+=	devel/gettext
LDFLAGS+=	-pthread

.include <bsd.port.mk>
