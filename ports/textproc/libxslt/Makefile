# $MirOS: ports/textproc/libxslt/Makefile,v 1.2 2005/12/28 00:56:18 bsiegert Exp $
# $OpenBSD: Makefile,v 1.34 2004/04/08 06:32:43 marcm Exp $

COMMENT=			XSLT C Library for GNOME

DISTNAME=		libxslt-1.1.15
CATEGORIES=		textproc

HOMEPAGE=		http://xmlsoft.org/XSLT/

MASTER_SITES=		ftp://xmlsoft.org/ \
			${MASTER_SITE_GNOME:=sources/libxslt/1.0/}

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		xml2::textproc/libxml

MODULES=		devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-libxml-include-prefix='${LOCALBASE}/include/'
CONFIGURE_ARGS+=	--without-python

.include <bsd.port.mk>
