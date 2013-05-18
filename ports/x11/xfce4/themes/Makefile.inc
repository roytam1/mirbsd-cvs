# $MirOS: ports/x11/xfce4/themes/Makefile.inc,v 1.7 2008/07/30 20:11:52 bsiegert Exp $

VSN?=		4.0.5
DASH_VER?=	1
CATEGORIES?=	x11 x11/xfce4 x11/xfce4/themes
MASTER_SITES?=	ftp://ftp.berlios.de/pub/xfce-goodies/4.0.5/ \
		http://xfce.org/archive/xfce-${VSN}/src/
DIST_SUBDIR?=	xfce4
HOMEPAGE?=	http://www.xfce.org/

# ?
PERMIT_DISTFILES_CDROM?=No
PERMIT_DISTFILES_FTP?=	No
PERMIT_PACKAGE_CDROM?=	No
PERMIT_PACKAGE_FTP?=	No

USE_X11=	Yes

GTK2=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
XFDESK=	:xfdesktop-*:x11/xfce4/desktop/xfdesktop

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		yes
MODULES+=		devel/pkgconfig
