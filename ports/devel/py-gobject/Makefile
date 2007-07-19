# $MirOS: ports/x11/py-gtk/Makefile,v 1.8 2007/05/07 19:48:16 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/16 21:12:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		gobject Python bindings

VERSION=		2.12.3
DISTNAME=		pygobject-${VERSION}
PKGNAME=		py-gobject-${VERSION}-${DASH_VER}
CATEGORIES=		devel

HOMEPAGE=		http://www.pygtk.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/pygobject/2.12/}

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS+=		glib-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0:glib2->=2.8:devel/glib

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-thread

# we cannot use python.port.mk because we do not use distutils
PYTHON_VERSION=		2.3
SUBST_VARS+=		PYTHON_VERSION

.include <bsd.port.mk>
