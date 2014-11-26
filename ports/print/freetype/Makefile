# $MirOS: ports/print/freetype/Makefile,v 1.6 2007/02/22 20:50:11 tg Exp $
# $OpenBSD: Makefile,v 1.31 2004/02/04 07:39:18 sturm Exp $
# $FreeBSD: Makefile,v 1.6 1998/06/21 02:42:33 jseger Exp $

COMMENT=		free and portable TrueType font rendering engine
COMMENT-doc=		documentation for FreeType
VERSION=		1.3.1
DASH_VER=		2
DISTNAME=		freetype-${VERSION}
PKGNAME-doc=		freetype-doc-${VERSION}-${DASH_VER}
CATEGORIES=		print
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=freetype/}
HOMEPAGE=		http://www.freetype.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf dest no-autoheader
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static --disable-nls

.include <mirports.sys.mk>

MULTI_PACKAGES= 	-doc
SUBPACKAGE?=

.if defined(PACKAGING) && ${SUBPACKAGE} == "-doc"
PKG_ARCH=		*
.endif

FT_DOC=			${PREFIX}/share/doc/freetype
SFT_DOC=		${WRKSRC}/docs
SRCTYPE=		*.txt *.htm *.lsm credits FAQ TODO

post-install:
	${INSTALL_DATA_DIR} ${FT_DOC}/image
	${INSTALL_DATA} ${SFT_DOC}/image/* ${FT_DOC}/image
	cd ${SFT_DOC}; ${INSTALL_DATA} ${SRCTYPE} ${FT_DOC}
	${INSTALL_DATA_DIR} ${PREFIX}/include/freetype1
	mv ${PREFIX}/include/freetype ${PREFIX}/include/freetype1

.include <bsd.port.mk>
