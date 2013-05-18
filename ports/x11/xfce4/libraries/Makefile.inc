# $MirOS: ports/x11/xfce4/libraries/Makefile.inc,v 1.6 2008/07/30 19:43:58 bsiegert Exp $

VSN?=		4.0.5
DASH_VER?=	1
CATEGORIES?=	x11 x11/xfce4 x11/xfce4/libraries

MASTER_SITES?=	http://xfce.org/archive/xfce-${VSN}/src/
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

MODULES+=	devel/gettext devel/pkgconfig

GLIB2=	glib-2.0.0.0::devel/glib
GTK2=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
UTIL=	xfce4util::x11/xfce4/libraries/libxfce4util

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		Yes
