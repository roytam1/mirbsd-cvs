# $MirOS: ports/x11/xfce4/desktop/Makefile.inc,v 1.2 2005/05/01 13:59:49 bsiegert Exp $

V?=		4.0.5
CATEGORIES?=	x11 x11/xfce4 x11/xfce4/desktop
MASTER_SITES?=	http://hannelore.f1.fhtw-berlin.de/mirrors/xfce4/xfce-${V}/src/
DIST_SUBDIR?=	xfce4
HOMEPAGE?=	http://www.xfce.org/

# xfprint is BSD, everything else is GPL
PERMIT_DISTFILES_CDROM?=Yes
PERMIT_DISTFILES_FTP?=	Yes
PERMIT_PACKAGE_CDROM?=	Yes
PERMIT_PACKAGE_FTP?=	Yes

USE_X11?=	Yes
MODULES+=	devel/gettext

DBH=	dbh.1.0::databases/dbh
GTK2=	gdk_pixbuf-2.0.0.14,gdk-x11-2.0.0.14,gtk-x11-2.0.0.14::x11/gtk+
GTHREAD=gthread-2.0.0.11::devel/glib
GUI=	xfcegui4.1.6::x11/xfce4/libraries/libxfcegui4
MCS=	xfce4mcs-client.1.1,xfce4mcs-manager.1.1::x11/xfce4/libraries/libxfce4mcs
MCSMANG=:xfce-mcs-manager-*:x11/xfce4/desktop/xfce-mcs-manager
STARTUP=startup-notification-1.0.0::devel/startup-notification
XML2=	xml2.7.10::textproc/libxml

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		yes
