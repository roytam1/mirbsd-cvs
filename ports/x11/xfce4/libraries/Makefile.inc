# $MirOS: ports/x11/xfce4/libraries/Makefile.inc,v 1.2 2005/05/01 13:59:50 bsiegert Exp $

V?=		4.0.5
CATEGORIES?=	x11 x11/xfce4 x11/xfce4/libraries

MASTER_SITES?=	http://hannelore.f1.fhtw-berlin.de/mirrors/xfce4/xfce-${V}/src/
DIST_SUBDIR?=	xfce4
HOMEPAGE?=	http://xfce.org/index.php?page=overview

# BSD:
#	libxfce4util
# GPL:
#	libxfce4mcs
#	libxfcegui4
PERMIT_DISTFILES_CDROM?=Yes
PERMIT_DISTFILES_FTP?=	Yes
PERMIT_PACKAGE_CDROM?=	Yes
PERMIT_PACKAGE_FTP?=	Yes

USE_X11?=	Yes
MODULES+=	devel/gettext

GLIB2=	glib-2.0.0.11::devel/glib
GTK2=	gdk_pixbuf-2.0.0.14,gdk-x11-2.0.0.14,gtk-x11-2.0.0.14::x11/gtk+
UTIL=	xfce4util.1.0::x11/xfce4/libraries/libxfce4util

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		Yes
