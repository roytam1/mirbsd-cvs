# $MirOS: ports/devel/desktop-file-utils/Makefile,v 1.2 2005/03/20 16:46:24 bsiegert Exp $

COMMENT=			utilities for working with desktop entries

VERSION=		0.10
DISTNAME=		desktop-file-utils-${VERSION}
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.freedesktop.org/wiki/Software/desktop-file-utils
MASTER_SITES=		http://www.freedesktop.org/software/desktop-file-utils/releases/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext

LIB_DEPENDS+=		glib-2.0.0.0::devel/glib \
			popt::devel/popt

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
