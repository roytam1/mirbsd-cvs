# $MirOS: ports/textproc/libxml/Makefile,v 1.10 2006/10/11 15:27:47 bsiegert Exp $
# $OpenBSD: Makefile,v 1.76 2004/04/21 04:42:26 robert Exp $

COMMENT=		XML parsing library
VERSION=		2.6.27
DISTNAME=		libxml2-${VERSION}
PKGNAME=		libxml-${VERSION}-0
CATEGORIES=		textproc
MASTER_SITES=		ftp://xmlsoft.org/libxml2/ \
			${HOMEPAGE}sources/ \
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
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--disable-libtool-lock

CPPFLAGS+=		-DMIRPORTS_LOCALBASE=\"${LOCALBASE:Q}\"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples
	env LD_LIBRARY_PATH=${PREFIX:Q}/lib DYLD_ROOT_PATH=${WRKINST:Q} \
		${PREFIX}/bin/xmlcatalog --noout --create \
		${PREFIX}/share/examples/xmlcatalog

.include <bsd.port.mk>
