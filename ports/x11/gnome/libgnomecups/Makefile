# $MirOS: ports/x11/gnome/libgnomecups/Makefile,v 1.3 2006/02/09 11:15:44 tg Exp $

COMMENT=			CUPS functionality hooks for GNOME

VERSION=		0.1.14
DISTNAME=		libgnomecups-${VERSION}
CATEGORIES=		x11/gnome print

HOMEPAGE=		http://www.gnome.org/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomecups/0.1/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		gthread-2.0.0.0,glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
			cups.2::print/cups

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
