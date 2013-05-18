# $MirOS: ports/x11/xfce4/plugins/Makefile.inc,v 1.7 2008/07/30 19:43:59 bsiegert Exp $

VSN?=		4.0.5
DASH_VER?=	1
CATEGORIES?=	x11 x11/xfce4 x11/xfce4-plugins
DIST_SUBDIR?=		xfce4

MASTER_SITE_EXTRAS=	http://xfce.org/archive/xfce-${VSN}/src/
MASTER_SITE_GOODIES=	http://download.berlios.de/xfce-goodies/
HOMEPAGE_EXTRAS=	http://www.xfce.org/en/extras.html
HOMEPAGE_GOODIES=	http://xfce-goodies.berlios.de/

# GPL:	xfce4-minicmd-plugin, xfce4-netload-plugin, xfce4-notes-plugin,
#	xfce4-datetime-plugin
# BSD:	xfce4-mixer, xfce4-systray, xfce4-toys, xfce4-trigger-launcher, 
#	xfce4-systemload-plugin, xfce4-battery-plugin, xfce4-showdesktop-plugin,
#	xfce4-diskperf-plugin, xfce4-clipman-plugin, xfce4-fsguard-plugin,
#	xfce4-wavelan-plugin, xfce4-xmms-plugin, xfce4-weather-plugin
PERMIT_DISTFILES_CDROM?=Yes
PERMIT_DISTFILES_FTP?=	Yes
PERMIT_PACKAGE_CDROM?=	Yes
PERMIT_PACKAGE_FTP?=	Yes

USE_X11=	Yes

DBH=	dbh::databases/dbh
GTK2=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
GTHREAD=gthread-2.0.0.0::devel/glib
GUI=	xfcegui4::x11/xfce4/libraries/libxfcegui4
MCS=	xfce4mcs-client,xfce4mcs-manager::x11/xfce4/libraries/libxfce4mcs
PANEL=	:xfce4-panel-*:x11/xfce4/desktop/xfce4-panel
STARTUP=startup-notification-1.0.0::devel/startup-notification
XML2=	xml2::textproc/libxml

BUILD_DEPENDS?=	${PANEL}
RUN_DEPENDS?=	${PANEL}

CONFIGURE_STYLE?=	autoconf
MODULES+=		devel/pkgconfig
AUTOCONF_NEW?=		Yes
