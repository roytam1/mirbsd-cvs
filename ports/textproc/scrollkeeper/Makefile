# $MirOS: ports/textproc/scrollkeeper/Makefile,v 1.5 2007/01/29 20:33:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2004/12/07 00:23:23 alek Exp $

COMMENT=		open documentation cataloging system

VERSION=		0.3.14
DISTNAME=		scrollkeeper-${VERSION}
DASH_VER=		2
CATEGORIES=		textproc

HOMEPAGE=		http://scrollkeeper.sourceforge.net/


MASTER_SITES=		${MASTER_SITE_GNOME:=sources/scrollkeeper/0.3/}
EXTRACT_SUFX=		.tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext

BUILD_DEPENDS=		:docbook->=4.2-1:textproc/docbook \
			:p5-XML-Parser-*:textproc/p5-XML-Parser
RUN_DEPENDS=		:docbook->=4.2-1:textproc/docbook \
			:libxml->=2.5.7-1:textproc/libxml
LIB_DEPENDS=		xml2::textproc/libxml \
			xslt::textproc/libxslt

USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 	--enable-static
CONFIGURE_ARGS+= 	--localstatedir=/var
CONFIGURE_ARGS+=	--with-omfdirs=${LOCALBASE}/share/omf
CONFIGURE_ARGS+=	--with-xml-catalog=${LOCALBASE}/db/xmlcatalog
CONFIGURE_ARGS+=	--with-partial-db-dir=db/scrollkeeper

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/scrollkeeper; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/* ${PREFIX}/share/examples/scrollkeeper/

.include <bsd.port.mk>
