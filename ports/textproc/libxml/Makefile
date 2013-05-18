# $MirOS: ports/textproc/libxml/Makefile,v 1.8 2006/02/01 16:28:03 tg Exp $
# $OpenBSD: Makefile,v 1.76 2004/04/21 04:42:26 robert Exp $

COMMENT=			XML parsing library
VERSION=		2.6.23
DISTNAME=		libxml2-${VERSION}
PKGNAME=		libxml-${VERSION}-0
CATEGORIES=		textproc
MASTER_SITES=		${HOMEPAGE}sources/ \
			ftp://xmlsoft.org/ \
			${MASTER_SITE_GNOME:=sources/libxml2/2.6/}
HOMEPAGE=		http://xmlsoft.org/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		converters/libiconv
MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--with-html-dir="${PREFIX}/share/doc"
CONFIGURE_ARGS+=	--with-html-subdir="libxml2/html"
CONFIGURE_ARGS+=	--with-iconv="${ICONV_PREFIX}"
CONFIGURE_ARGS+=	--with-zlib
CONFIGURE_ARGS+=	--without-python
CONFIGURE_ARGS+=	--without-readline
CONFIGURE_ARGS+=	--without-threads

CPPFLAGS+=		-DMIRPORTS_LOCALBASE=\"${LOCALBASE:Q}\"

.include <bsd.port.mk>
