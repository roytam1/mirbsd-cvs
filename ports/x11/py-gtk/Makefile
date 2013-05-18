# $MirOS: ports/x11/py-gtk/Makefile,v 1.6 2006/02/09 11:15:54 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/16 21:12:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			gtk+2 Python bindings

V=		2.0.0
DISTNAME=	pygtk-${V}
PKGNAME=	py-gtk2-${V}-0
CATEGORIES=	x11

HOMEPAGE=	http://www.pygtk.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNOME:=sources/pygtk/2.0/}

MODULES=	converters/libiconv lang/python devel/pkgconfig

MODPY_DISTUTILS_BUILDARGS=	--enable-threading

BUILD_DEPENDS=	:py-Numeric-*:math/py-Numeric
LIB_DEPENDS=	gthread-2.0.0.0::devel/glib \
		glade-2.0.0.0::devel/libglade \
		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	${CONFIGURE_SHARED} --enable-thread
CONFIGURE_ENV=	PYTHON=${MODPY_BIN}

NO_REGRESS=	Yes

EXAMPLESDIR=	${PREFIX}/share/examples/py-gtk2

pre-build:
	@perl -pi -e 's,%%PREFIX%%,${PREFIX},g' \
		${WRKSRC}/codegen/pygtk-codegen-2.0.in

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	cd ${WRKSRC}/examples; tar cf - . | tar xf - -C ${EXAMPLESDIR}

.include <bsd.port.mk>
