# $MirOS: ports/graphics/lcms2/Makefile,v 1.1 2013/09/11 18:14:16 tg Exp $
# $OpenBSD: Makefile,v 1.7 2013/03/30 15:49:43 ajacoutot Exp $

COMMENT=		color management library
DISTNAME=		lcms2-2.4
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=lcms/}
HOMEPAGE=		http://www.littlecms.com/

# MIT
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		jpeg::graphics/jpeg
LIB_DEPENDS+=		tiff::graphics/tiff

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.62
AUTOMAKE_VERSION=	1.9

DOCDIR=			${PREFIX}/share/doc/lcms2

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	cd ${WRKSRC}/doc; \
	    ${INSTALL_DATA} LittleCMS2.??API.pdf ${DOCDIR}/api.pdf; \
	    ${INSTALL_DATA} LittleCMS2*Plugin?API.pdf ${DOCDIR}/plugin-api.pdf; \
	    ${INSTALL_DATA} LittleCMS2*tutorial.pdf ${DOCDIR}/tutorial.pdf

.include <bsd.port.mk>
