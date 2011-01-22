# $MirOS: ports/devel/py-gobject/Makefile,v 1.2 2007/07/19 20:34:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/16 21:12:50 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		gobject Python bindings
VERSION=		2.14.2
DISTNAME=		pygobject-${VERSION}
PKGNAME=		py-gobject-${VERSION}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://www.pygtk.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/pygobject/2.14/}

MODULES=		devel/gettext devel/pkgconfig lang/python
LIB_DEPENDS+=		glib-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0:glib2->=2.8:devel/glib

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-thread
MODPY_USE_DISTUTILS=	No

.include <bsd.port.mk>
