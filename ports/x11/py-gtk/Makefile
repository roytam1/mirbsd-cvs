# $MirOS: ports/x11/py-gtk/Makefile,v 1.10 2011/01/22 21:31:57 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/16 21:12:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		GTK+2 Python bindings
VSN=			2.12.1
DISTNAME=		pygtk-${VSN}
PKGNAME=		py-gtk2-${VSN}-${DASH_VER}
CATEGORIES=		x11 x11/gnome
HOMEPAGE=		http://www.pygtk.org/

# LGPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/pygtk/2.12/}

MODULES+=		converters/libiconv
MODULES+=		lang/python
MODULES+=		devel/pkgconfig

MODPY_USE_DISTUTILS=	No

B_R_DEPENDS+=		:py-cairo->=1.2:graphics/py-cairo
B_R_DEPENDS+=		:py-gobject->=2.14:devel/py-gobject
B_R_DEPENDS+=		:py-Numeric-*:math/py-Numeric
LIB_DEPENDS+=		atk-1.0.0.0:atk->=1.12:devel/atk
LIB_DEPENDS+=		glade-2.0.0.0::devel/libglade
LIB_DEPENDS+=		gthread-2.0.0.0::devel/glib \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0:gtk+2->=2.12:x11/gtk+

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-thread
CONFIGURE_ENV+=		PYTHON=${MODPY_BIN:Q}

NO_REGRESS=		Yes

EXAMPLESDIR=		${PREFIX}/share/examples/py-gtk2

pre-configure:
	@find ${WRKDIST} -name \*.py | \
	    xargs perl -i -pe 's:^#!/usr/bin/env python:#!${MODPY_BIN}:'

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	cd ${WRKSRC}/examples; tar cf - . | tar xf - -C ${EXAMPLESDIR}
	mv ${PREFIX:Q}/share/gtk-doc/html/pygtk ${PREFIX:Q}/share/doc/py-gtk2
	rm -rf ${PREFIX:Q}/share/gtk-doc

.include <bsd.port.mk>
