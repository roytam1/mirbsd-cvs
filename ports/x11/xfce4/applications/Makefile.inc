# $MirOS: ports/x11/xfce4/applications/Makefile.inc,v 1.5 2008/07/30 19:43:58 bsiegert Exp $

VSN?=		4.0.5
DASH_VER?=	1

CATEGORIES?=	x11 x11/xfce4 x11/xfce4/applications
MASTER_SITES?=	http://xfce.org/archive/xfce-${VSN}/src/
DIST_SUBDIR?=	xfce4
HOMEPAGE?=	http://xfce.org/index.php?page=overview

# BSD:
#	xfce4-session
# GPL:
#	xfcalendar
#	xfce4-iconbox
#	xfce4-menueditor
PERMIT_DISTFILES_CDROM?=Yes
PERMIT_DISTFILES_FTP?=	Yes
PERMIT_PACKAGE_CDROM?=	Yes
PERMIT_PACKAGE_FTP?=	Yes

MODULES+=		devel/pkgconfig
BUILD_DEPENDS?=		:xfce-mcs-manager-*:x11/xfce4/desktop/xfce-mcs-manager
RUN_DEPENDS?=		:xfce-mcs-manager-*:x11/xfce4/desktop/xfce-mcs-manager

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW?=		Yes
USE_X11=		Yes
