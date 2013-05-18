# $MirOS: ports/x11/gnome/libgnomeprint/Makefile,v 1.6 2006/02/09 11:15:45 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/12/15 13:57:56 alek Exp $

COMMENT=		"printing framework for GNOME"
COMMENT-cups=		"CUPS module for printing framework for GNOME"

VERSION=		2.8.1
DASH_VER=		-1
DISTNAME=		libgnomeprint-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
PKGNAME-cups=		libgnomeprint-cups-${VERSION}${DASH_VER}
CATEGORIES=		x11/gnome devel

HOMEPAGE=		http://www.gnome.org/projects/gnome-print/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomeprint/2.8/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		art_lgpl_2.5::graphics/libart \
			glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
			pango-1.0.0.0,pangoft2-1.0.0.0::devel/pango \
			popt.0::devel/popt \
			xml2.2.6::textproc/libxml

PSEUDO_FLAVORS=		no_cups
FLAVOR?=

MULTI_PACKAGES=
.if ${FLAVOR:L:Mno_cups}
CONFIGURE_ARGS+=	--without-cups
.else
BUILD_DEPENDS+=		::x11/gnome/libgnomecups
CONFIGURE_ARGS+=	--with-cups
MULTI_PACKAGES+=	-cups
.endif

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
SUBST_VARS=		VERSION

.if defined(PACKAGING)
. if defined(SUBPACKAGE) && !empty(SUBPACKAGE) && ${SUBPACKAGE} == "-cups"
LIB_DEPENDS=		gnomeprint-2-2::x11/gnome/libgnomeprint \
			gnomecups-1.0::x11/gnome/libgnomecups \
			cups.2::print/cups
. endif
.endif

.include <bsd.port.mk>
