# $MirOS: ports/textproc/xmlstarlet/Makefile,v 1.1 2008/08/16 21:56:45 tg Exp $
# $NetBSD: Makefile,v 1.8 2006/04/06 06:22:52 reed Exp $

CATEGORIES=		textproc
COMMENT=		command line utilities for XML manipulation
DISTNAME=		xmlstarlet-1.0.1
DASH_VER=		1
HOMEPAGE=		http://xmlstar.sourceforge.net/

# MIT
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=xmlstar/}

MODULES+=		converters/libiconv
LIB_DEPENDS+=		xml2::textproc/libxml \
			xslt::textproc/libxslt

CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.4
CONFIGURE_ARGS+=	--with-libxml-prefix=${LOCALBASE:Q} \
			--with-libxslt-prefix=${LOCALBASE:Q} \
			--with-libiconv-prefix=${ICONV_PREFIX:Q}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xmlstarlet
	${INSTALL_DATA} ${WRKSRC}/doc/xmlstarlet.txt \
	    ${PREFIX}/share/doc/xmlstarlet/xmlstarlet.txt
	${INSTALL_DATA} ${WRKSRC}/doc/xmlstarlet-ug.pdf \
	    ${PREFIX}/share/doc/xmlstarlet/xmlstarlet.pdf
	cd ${PREFIX}/bin && mv -f xml xmlstarlet

.include <bsd.port.mk>
