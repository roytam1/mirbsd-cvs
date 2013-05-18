# $OpenBSD: Makefile,v 1.21 2002/12/29 20:08:46 fgsch Exp $

COMMENT=	"color font rendering library for X"

DISTNAME=	fnlib-0.5
CATEGORIES=	graphics
MASTER_SITES=	ftp://ftp.squish.org/pub/enlightenment/enlightenment/libs/ \
		ftp://ftp.shellhung.org/pub/Mirror/enlightenment/fnlib/ \
		ftp://ftp.dti.ad.jp/pub/X/enlightenment/enlightenment/libs/

LIB_DEPENDS=	Imlib.19::graphics/imlib


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/fnlib
	mv -f ${WRKINST}${SYSCONFDIR}/* ${PREFIX}/share/examples/fnlib

.include <bsd.port.mk>
