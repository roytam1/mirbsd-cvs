# $MirOS: ports/x11/sawfish/Makefile,v 1.6 2007/05/07 19:48:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2003/05/15 04:39:16 margarida Exp $

COMMENT=	extensible window manager

VERSION=	0.36
DISTNAME=	sawfish-${VERSION}
CATEGORIES=	x11

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=sawmill/}

HOMEPAGE=       http://sawmill.sourceforge.net/

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	:rep-gtk-*:x11/rep-gtk
LIB_DEPENDS=	gtk.1.2::x11/gtk+1 \
		glib.1.2::devel/glib1 \
		rep.10::lang/librep \
		Imlib.19,gdk_imlib.19::graphics/imlib

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SUBST_VARS=	OPSYS_VER VERSION

USE_X11=	Yes
USE_CXX=	Yes # depends on libungif, which uses CXX
USE_GMAKE=      Yes
CONFIGURE_STYLE= gnu
MODGNU_RECURSE_DIRS=	${WRKSRC}/etc
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --without-audiofile --without-esd \
		 --disable-capplet --disable-themer \
		 --disable-gnome-widgets --disable-linguas

NO_REGRESS=	Yes

.include <bsd.port.mk>
