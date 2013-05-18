# $OpenBSD: Makefile,v 1.11 2003/12/26 17:07:56 naddy Exp $

COMMENT=			C library to produce PDF files

DISTNAME=		pdflib-4.0.3
CATEGORIES=     	print

HOMEPAGE=		http://www.pdflib.com/pdflib/


PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.pdflib.com/pdflib/download/

LIB_DEPENDS=		tiff.35::graphics/tiff
MODULES+=		graphics/png

CONFIGURE_STYLE=	autoconf dest
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/config
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--with-tifflib \
			--with-pnglib \
			--with-zlib \
			--without-perl \
			--without-java \
			--without-py \
			--without-tcl

CONFIGURE_ENV=		LIBS="-lm"
MAKE_ENV=		${CONFIGURE_ENV}

REGRESS_TARGET=		test

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pdflib
	${INSTALL_DATA} ${WRKSRC}/doc/* ${PREFIX}/share/doc/pdflib

.include <bsd.port.mk>
