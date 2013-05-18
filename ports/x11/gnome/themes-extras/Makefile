# $MirOS: ports/x11/gnome/themes-extras/Makefile,v 1.4 2006/09/14 00:15:22 tg Exp $

COMMENT=		themes collection for GNOME

VERSION=		0.4
# XXX is this correct?
DISTNAME=		gnome-themes-extras-${VERSION}-${DASH_VER}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-themes-extras/0.4/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext

BUILD_DEPENDS=		:intltool->=0.23:textproc/intltool \
			${RUN_DEPENDS}
RUN_DEPENDS=		:gtk-engines2->=2.2.0:x11/gtk-engines2
LIB_DEPENDS= 		gnomeui-2.0::x11/gnome/libgnomeui

USE_X11=		Yes
CONFIGURE_STYLE= 	gnu automake

.include <bsd.port.mk>
