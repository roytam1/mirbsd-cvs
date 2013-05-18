# $MirOS: ports/x11/xfce4/desktop/Makefile.inc,v 1.7 2008/07/30 19:43:58 bsiegert Exp $

VSN?=		4.0.5
DASH_VER?=	1
CATEGORIES?=	x11 x11/xfce4 x11/xfce4/desktop
MASTER_SITES?=	http://xfce.org/archive/xfce-${VSN}/src/
DIST_SUBDIR?=	xfce4
HOMEPAGE?=	http://www.xfce.org/

# xfprint is BSD, everything else is GPL
PERMIT_DISTFILES_CDROM?=Yes
PERMIT_DISTFILES_FTP?=	Yes
PERMIT_PACKAGE_CDROM?=	Yes
PERMIT_PACKAGE_FTP?=	Yes

USE_X11=	Yes
MODULES+=	devel/gettext devel/pkgconfig

DBH=	dbh::databases/dbh
GTK2=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
GTHREAD=gthread-2.0.0.0::devel/glib
GUI=	xfcegui4::x11/xfce4/libraries/libxfcegui4
MCS=	xfce4mcs-client,xfce4mcs-manager::x11/xfce4/libraries/libxfce4mcs
MCSMANG=:xfce-mcs-manager-*:x11/xfce4/desktop/xfce-mcs-manager
STARTUP=startup-notification-1.0.0::devel/startup-notification
XML2=	xml2::textproc/libxml

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		yes
