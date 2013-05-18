# $MirOS: ports/devel/libgsf/Makefile,v 1.4 2006/02/09 11:11:24 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/12/10 20:33:59 marcm Exp $

COMMENT=		"GNOME Structured File library"
COMMENT-gnome=		"GNOME specific extensions to libgsf"

VERSION=		1.11.1
DISTNAME=		libgsf-${VERSION}
PKGNAME=		libgsf-${VERSION}-1
PKGNAME-gnome=		libgsf-gnome-${VERSION}-1
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgsf/1.11/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		bz2.10.2::archivers/bzip2 \
			xml2.2.6::textproc/libxml \
			glib-2.0.0.11,gobject-2.0.0.11::devel/glib

USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

PSEUDO_FLAVORS=	no_gnome
FLAVOR?=

MULTI_PACKAGES=
.if !${FLAVOR:L:Mno_gnome}
MULTI_PACKAGES+= -gnome
.endif
SUBPACKAGE?=

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-gnome"
LIB_DEPENDS+=   gnomevfs-2::x11/gnome/vfs2 \
                gsf-1::devel/libgsf
. endif
.else
. if ${MULTI_PACKAGES:M-gnome}
LIB_DEPENDS+=   gnomevfs-2::x11/gnome/vfs2
. endif
.endif

.if ${MULTI_PACKAGES:M-gnome}
CONFIGURE_ARGS+= --with-gnome
.else
CONFIGURE_ARGS+= --without-gnome
.endif

.include <bsd.port.mk>
