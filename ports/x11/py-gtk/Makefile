# $MirOS: ports/x11/py-gtk/Makefile,v 1.9 2009/08/16 17:19:32 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/16 21:12:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		GTK+2 Python bindings
VSN=			2.0.0
DASH_VER=		1
DISTNAME=		pygtk-${VSN}
PKGNAME=		py-gtk2-${VSN}-${DASH_VER}
CATEGORIES=		x11
HOMEPAGE=		http://www.pygtk.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/pygtk/2.0/}

MODULES+=		converters/libiconv
MODULES+=		lang/python
MODULES+=		devel/pkgconfig

MODPY_DISTUTILS_BUILDARGS=	--enable-threading

BUILD_DEPENDS=	:py-Numeric-*:math/py-Numeric
LIB_DEPENDS=	gthread-2.0.0.0::devel/glib \
		glade-2.0.0.0::devel/libglade \
		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-thread
CONFIGURE_ENV+=		PYTHON=${MODPY_BIN:Q}

NO_REGRESS=		Yes

EXAMPLESDIR=		${PREFIX}/share/examples/py-gtk2

pre-build:
	@perl -pi -e 's,%%PREFIX%%,${PREFIX},g' \
		${WRKSRC}/codegen/pygtk-codegen-2.0.in

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	cd ${WRKSRC}/examples; tar cf - . | tar xf - -C ${EXAMPLESDIR}

.include <bsd.port.mk>
