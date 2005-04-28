# $MirOS: ports/graphics/imlib/Makefile,v 1.2 2005/03/27 19:11:11 tg Exp $
# $OpenBSD: Makefile,v 1.46 2003/11/14 23:52:42 brad Exp $
# $FreeBSD: Makefile,v 1.45 1999/03/09 01:08:57 nectar Exp $

COMMENT=	"image manipulation library for X11"
V=		1.9.15
DISTNAME=	imlib-${V}
CATEGORIES=	graphics devel
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/imlib/1.9/}
HOMEPAGE=	http://freshmeat.net/projects/imlib/

MODULES=	devel/gettext
LIB_DEPENDS= 	gtk.1.2,gdk.1.2::x11/gtk+1 \
		jpeg.62::graphics/jpeg \
		png.2::graphics/png \
		tiff.35::graphics/tiff

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

VMEM_WARNING=	Yes
USE_X11=	Yes
USE_GMAKE=	Yes
SEPARATE_BUILD=	concurrent
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=${CONFIGURE_SHARED}
CONFIGURE_ARGS+=--disable-modules
CPPFLAGS+=	-I${LOCALBASE}/include/libpng

FLAVORS=	no_cxx
FLAVOR?=

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=--disable-gif
.else
LIB_DEPENDS+=	ungif.5::graphics/libungif
USE_CXX=	Yes
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/aclocal
	${INSTALL_DATA} ${WRKSRC}/imlib.m4 ${PREFIX}/share/aclocal/

.include <bsd.port.mk>
