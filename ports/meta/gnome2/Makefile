# $MirOS: ports/meta/gnome2/Makefile,v 1.10 2008/06/25 18:40:48 bsiegert Exp $

COMMENT=		meta package to install all of GNOME 2
VERSION=		2.18.2
DASH_VER=		2
PKGNAME=		meta-gnome2-${VERSION}-${DASH_VER}
CATEGORIES=		meta x11/gnome
HOMEPAGE=		http://www.gnome.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

DISTFILES=		

# GPL/LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

NO_CHECKSUM=		Yes
NO_BUILD=		Yes
PLIST=			/dev/null
PKG_ARCH=		*
USE_X11=		Yes # GNOME needs X11
USE_CXX=		Yes # multiple dependencies use CXX

B_R_DEPENDS+=		:libxml->=2.6.32:textproc/libxml
B_R_DEPENDS+=		::devel/gconf
B_R_DEPENDS+=		::devel/desktop-file-utils
B_R_DEPENDS+=		::x11/gnome/mime-data
B_R_DEPENDS+=		::x11/gnome/vfs2
B_R_DEPENDS+=		::devel/libaudiofile
B_R_DEPENDS+=		::audio/esound
B_R_DEPENDS+=		::x11/gnome/libgnome
B_R_DEPENDS+=		::graphics/libart
B_R_DEPENDS+=		::devel/libglade
B_R_DEPENDS+=		::x11/gnome/libgnomecanvas
B_R_DEPENDS+=		::x11/gnome/libbonoboui
B_R_DEPENDS+=		::x11/hicolor-icon-theme
B_R_DEPENDS+=		::x11/gnome/icon-theme
B_R_DEPENDS+=		::x11/gnome/keyring
B_R_DEPENDS+=		::x11/gnome/libgnomeui
B_R_DEPENDS+=		::devel/startup-notification
B_R_DEPENDS+=		::x11/gtk-engines
B_R_DEPENDS+=		::textproc/scrollkeeper
B_R_DEPENDS+=		::x11/gnome/desktop
B_R_DEPENDS+=		::devel/libwnck
B_R_DEPENDS+=		::devel/libsoup
B_R_DEPENDS+=		::x11/gnome/evolution-data-server
B_R_DEPENDS+=		::x11/gnome/menus
B_R_DEPENDS+=		::x11/gnome/panel
B_R_DEPENDS+=		::devel/vte
B_R_DEPENDS+=		::x11/gnome/terminal
B_R_DEPENDS+=		::devel/libgtop
B_R_DEPENDS+=		::x11/gnome/gail
B_R_DEPENDS+=		::x11/libxklavier
B_R_DEPENDS+=		::x11/gnome/applets2
B_R_DEPENDS+=		::x11/gnome/metacity
B_R_DEPENDS+=		::textproc/libcroco
B_R_DEPENDS+=		::x11/gnome/librsvg
B_R_DEPENDS+=		::x11/gnome/libgnomeprint
B_R_DEPENDS+=		::x11/gnome/libgnomeprintui
B_R_DEPENDS+=		::x11/gnome/nautilus
B_R_DEPENDS+=		::x11/gnome/controlcenter2
B_R_DEPENDS+=		::x11/gnome/session
B_R_DEPENDS+=		::x11/gnome/utils
#B_R_DEPENDS+=		::x11/gnome/eog

do-install:
	# Nothing to do

.include <bsd.port.mk>
