# $MirOS: ports/textproc/libcroco/Makefile,v 1.3 2006/02/09 11:15:30 tg Exp $

COMMENT=			parse and manipulate CSS (Cascading Style Sheets)

VERSION=		0.6.0
DISTNAME=		libcroco-${VERSION}
CATEGORIES=		textproc x11/gnome

HOMEPAGE=		http://www.freespiders.org/projects/libcroco/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libcroco/0.6/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		glib-2.0.0.0::devel/glib \
			xml2::textproc/libxml

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
