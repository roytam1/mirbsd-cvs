# $MirOS: ports/textproc/xpdf/Makefile,v 1.3 2006/09/14 00:14:28 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/04/06 02:35:44 brad Exp $

COMMENT=		PDF viewer for X
DISTNAME=		xpdf-3.00
CATEGORIES=		textproc x11
MASTER_SITES=		ftp://ftp.foolabs.com/pub/xpdf/
HOMEPAGE=		http://www.foolabs.com/xpdf/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
USE_MOTIF=		lesstif #openmotif
LIB_DEPENDS+=		t1x.3,t1.3::devel/t1lib
RUN_DEPENDS+=		::print/ghostscript/fonts-std
USE_CXX=		Yes
NO_REGRESS=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-multithreaded \
			--without-Sgm-library \
			--without-libpaper-library
CPPFLAGS+=		-I${.CURDIR} -I${X11BASE}/include/freetype2

STRIP?=			strip

post-install:
	cd ${PREFIX}/bin && \
	    ${STRIP} pdffonts pdfimages pdfinfo pdftoppm pdftops pdftotext xpdf
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xpdf
	${INSTALL_DATA} ${WRKSRC}/doc/sample-xpdfrc \
	    ${PREFIX}/share/examples/xpdf/xpdfrc
	-rm -f ${WRKINST}/etc/xpdfrc

.include <bsd.port.mk>
