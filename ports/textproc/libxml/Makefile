# $MirOS: ports/textproc/libxml/Makefile,v 1.16 2008/03/16 17:36:30 bsiegert Exp $
# $OpenBSD: Makefile,v 1.76 2004/04/21 04:42:26 robert Exp $

COMMENT=		XML parsing library
VERSION=		2.6.31
DASH_VER=		2
DISTNAME=		libxml2-${VERSION}
PKGNAME=		libxml-${VERSION}-${DASH_VER}
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

FLAVOURS=		python
FLAVOUR?=		python

MODULES=		converters/libiconv
MODULES+=		devel/pkgconfig

SUBST_VARS+=		VERSION

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--with-html-dir="${PREFIX}/share/doc"
CONFIGURE_ARGS+=	--with-html-subdir="libxml2/html"
CONFIGURE_ARGS+=	--with-iconv="${ICONV_PREFIX}"
CONFIGURE_ARGS+=	--with-zlib
CONFIGURE_ARGS+=	--without-readline
CONFIGURE_ARGS+=	--without-threads

CPPFLAGS+=		-DMIRPORTS_LOCALBASE=\"${LOCALBASE:Q}\"

.if ${FLAVOUR:L:Mpython}
CONFIGURE_ARGS+=	--with-python
B_R_DEPENDS+=		::lang/python/2.3
.else
CONFIGURE_ARGS+=	--without-python
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples
	env LD_LIBRARY_PATH=${PREFIX:Q}/lib DYLD_ROOT_PATH=${WRKINST:Q} \
		${PREFIX}/bin/xmlcatalog --noout --create \
		${PREFIX}/share/examples/xmlcatalog

.include <bsd.port.mk>
