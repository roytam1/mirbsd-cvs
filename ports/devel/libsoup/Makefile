# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/11/23 21:34:27 espie Exp $

COMMENT=		"a SOAP implementation in C"

DISTNAME=		libsoup-2.2.1
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libsoup/2.2/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		glib-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0::devel/glib \
			xml2.2.6::textproc/libxml
MODULES+=		devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

API_VERSION=		2.2
SUBST_VARS=		API_VERSION

FLAVORS=		ssl
FLAVOR?=

.if ${FLAVOR:L:Mssl}
CONFIGURE_ARGS+=	--enable-ssl
LIB_DEPENDS+=		gnutls.12::security/gnutls
.else
CONFIGURE_ARGS+=	--disable-ssl
.endif

.include <bsd.port.mk>
