# $MirOS: ports/mailnews/pan/Makefile,v 1.6 2006/09/14 00:10:44 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/04/02 19:07:05 sturm Exp $

COMMENT=	powerful Gtk+2 newsreader

VER=		0.14.2
DISTNAME=	pan-${VER}
PKGNAME=	${DISTNAME}-1
CATEGORIES=	news x11
MASTER_SITES=	http://pan.rebelbase.com/download/releases/${VER}/SOURCE/

LIB_DEPENDS=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.5::x11/gtk+ \
		gtk-x11-2.0.0.5::x11/gtk+ \
		gthread-2.0.0.0::devel/glib \
		xml2.2.6::textproc/libxml \
		gnet-2.0.0.3::net/gnet
MODULES+=	devel/pkgconfig

HOMEPAGE=	http://pan.rebelbase.com/

MODULES=	devel/gettext

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=--disable-gtkspell
USE_X11=	Yes
USE_CXX=	Yes # depends on gnet, which uses CXX

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pan
	${INSTALL_DATA} ${WRKBUILD}/docs/faq.html ${PREFIX}/share/doc/pan

.include <bsd.port.mk>
