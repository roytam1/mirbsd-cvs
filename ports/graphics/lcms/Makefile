# $MirOS: ports/graphics/lcms/Makefile,v 1.3 2006/01/11 17:19:46 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/03 05:15:16 brad Exp $

COMMENT=			color management library
DISTNAME=		lcms-1.15
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=lcms/}
HOMEPAGE=		http://www.littlecms.com/
LIB_DEPENDS+=		jpeg::graphics/jpeg \
			tiff::graphics/tiff

# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/lcms
	${INSTALL_DATA} ${WRKSRC}/doc/* ${PREFIX}/share/doc/lcms/

.include <bsd.port.mk>
