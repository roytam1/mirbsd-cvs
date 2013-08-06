# 2.7.6 -> 2.7.7
BROKEN=			needs MFC to work with -current libz

# $MirOS: ports/textproc/libxml/Makefile,v 1.20 2010/11/19 17:15:12 bsiegert Exp $
# $OpenBSD: Makefile,v 1.76 2004/04/21 04:42:26 robert Exp $

COMMENT=		XML parsing library
MODPY_EGG_VERSION=	2.6.32
DASH_VER=		1
DISTNAME=		libxml2-${MODPY_EGG_VERSION}
PKGNAME=		libxml-${MODPY_EGG_VERSION}-${DASH_VER}
CATEGORIES=		textproc
MASTER_SITES=		ftp://xmlsoft.org/libxml2/old/ \
			${HOMEPAGE}sources/ \
			${MASTER_SITE_GNOME:=sources/libxml2/2.6/}
HOMEPAGE=		http://xmlsoft.org/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		converters/libiconv
MODULES+=		devel/pkgconfig
MODULES+=		lang/python

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODPY_USE_DISTUTILS=	No
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--with-html-dir=${PREFIX:Q}/share/doc
CONFIGURE_ARGS+=	--with-html-subdir=libxml2/html
CONFIGURE_ARGS+=	--with-iconv=${ICONV_PREFIX:Q}
CONFIGURE_ARGS+=	--with-zlib
CONFIGURE_ARGS+=	--without-readline
CONFIGURE_ARGS+=	--without-threads
CONFIGURE_ARGS+=	--with-python=${LOCALBASE}/bin/python${MODPY_VERSION}

CPPFLAGS+=		-DMIRPORTS_LOCALBASE=\"${LOCALBASE:Q}\"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/examples
	env LD_LIBRARY_PATH=${PREFIX:Q}/lib DYLD_ROOT_PATH=${WRKINST:Q} \
	    ${PREFIX:Q}/bin/xmlcatalog --noout --create \
	    ${PREFIX:Q}/share/examples/xmlcatalog

.include <bsd.port.mk>
