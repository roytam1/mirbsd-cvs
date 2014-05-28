# $MirOS: ports/textproc/libxslt/Makefile,v 1.6 2008/08/27 10:13:10 tg Exp $
# $OpenBSD: Makefile,v 1.34 2004/04/08 06:32:43 marcm Exp $

COMMENT=		XSLT C Library for GNOME
MODPY_EGG_VERSION=	1.1.24
DASH_VER=		1
DISTNAME=		libxslt-${MODPY_EGG_VERSION}
CATEGORIES=		textproc
HOMEPAGE=		http://xmlsoft.org/XSLT/
MASTER_SITES=		ftp://xmlsoft.org/libxml2/ \
			${MASTER_SITE_GNOME:=sources/libxslt/1.1/}

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		gcrypt::security/libgcrypt
MODULES+=		devel/pkgconfig
MODULES+=		lang/python
MODPY_USE_DISTUTILS=	No

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--with-libxml-include-prefix=${LOCALBASE:Q}/include/
CONFIGURE_ARGS+=	--with-python=${MODPY_BIN:Q}
CONFIGURE_ARGS+=	--with-crypto

.include <bsd.port.mk>
