# $MirOS: ports/meta/gnome2/Makefile,v 1.4 2006/11/09 18:35:52 tg Exp $

COMMENT=			meta-package to install all of GNOME 2
VERSION=		2.8.1
DASH_VER=		-0
PKGNAME=		meta-gnome2-${VERSION}${DASH_VER}
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

RUN_DEPENDS+=		::devel/gconf
RUN_DEPENDS+=		::devel/desktop-file-utils
RUN_DEPENDS+=		::x11/gnome/mime-data
RUN_DEPENDS+=		::x11/gnome/vfs2
RUN_DEPENDS+=		::devel/libaudiofile
RUN_DEPENDS+=		::audio/esound
RUN_DEPENDS+=		::x11/gnome/libgnome
RUN_DEPENDS+=		::graphics/libart
RUN_DEPENDS+=		::devel/libglade
RUN_DEPENDS+=		::x11/gnome/libgnomecanvas
RUN_DEPENDS+=		::x11/gnome/libbonoboui
RUN_DEPENDS+=		::x11/hicolor-icon-theme
RUN_DEPENDS+=		::x11/gnome/icon-theme
RUN_DEPENDS+=		::x11/gnome/keyring
RUN_DEPENDS+=		::x11/gnome/libgnomeui
RUN_DEPENDS+=		::devel/startup-notification
RUN_DEPENDS+=		::x11/gtk-engines
RUN_DEPENDS+=		::textproc/scrollkeeper
RUN_DEPENDS+=		::x11/gnome/desktop
RUN_DEPENDS+=		::devel/libwnck
RUN_DEPENDS+=		::devel/libsoup
RUN_DEPENDS+=		::x11/gnome/evolution-data-server
RUN_DEPENDS+=		::x11/gnome/panel
RUN_DEPENDS+=		::x11/gnome/session
RUN_DEPENDS+=		::devel/vte
RUN_DEPENDS+=		::x11/gnome/terminal
RUN_DEPENDS+=		::devel/libgtop
RUN_DEPENDS+=		::x11/gnome/gail
RUN_DEPENDS+=		::x11/libxklavier1
RUN_DEPENDS+=		::x11/gnome/applets2
RUN_DEPENDS+=		::x11/gnome/metacity
RUN_DEPENDS+=		::x11/gnome/librsvg
RUN_DEPENDS+=		::x11/gnome/nautilus
RUN_DEPENDS+=		::x11/gnome/controlcenter2
RUN_DEPENDS+=		::x11/gnome/eog

BUILD_DEPENDS+=		${RUN_DEPENDS}

do-install:
	# Nothing to do

.include <bsd.port.mk>
