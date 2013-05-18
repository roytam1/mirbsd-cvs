# $MirOS: ports/graphics/libungif/Makefile,v 1.7 2006/09/14 00:09:59 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/04/18 20:58:45 brad Exp $

COMMENT=	tools and library routines for working with GIF images
DISTNAME=	libungif-4.1.3
PKGNAME=	${DISTNAME}-0
CATEGORIES=	graphics
USE_CXX=	Yes
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=giflib/}
EXTRACT_SUFX=	.tar.bz2
HOMEPAGE=	http://sourceforge.net/projects/giflib/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--without-x

DOCS=			COPYING UNCOMPRESSED_GIF
HTMLDOCS=		*.html *.txt *.png
DOCSDIR=		${PREFIX}/share/doc/libungif

post-install:
	@cd ${PREFIX}/lib; \
	for f in libungif.*; do \
		g=`echo $$f | sed -e s#libungif#libgif#g`; \
		[[ $$f = libungif.la ]] || ln -sf $$f $$g; \
	done && \
	sed -e s#libungif#libgif#g libungif.la > libgif.la && \
	chown ${LIBOWN}:${LIBGRP} libgif.la && \
	chmod 755 libgif.la
	${INSTALL_DATA_DIR} ${DOCSDIR}
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${DOCSDIR}
	${INSTALL_DATA_DIR} ${DOCSDIR}/html
	cd ${WRKSRC}/doc; ${INSTALL_DATA} ${HTMLDOCS} ${DOCSDIR}/html

.include <bsd.port.mk>
