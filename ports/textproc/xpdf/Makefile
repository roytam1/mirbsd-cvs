# $MirOS: ports/textproc/xpdf/Makefile,v 1.1.7.1 2005/03/18 15:53:06 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/04/06 02:35:44 brad Exp $

COMMENT=	"PDF viewer for X"

DISTNAME=	xpdf-3.00
CATEGORIES=	textproc x11

MASTER_SITES=	ftp://ftp.foolabs.com/pub/xpdf/

HOMEPAGE=	http://www.foolabs.com/xpdf/

LIB_DEPENDS+=	t1x.3,t1.3::devel/t1lib
RUN_DEPENDS+=	::print/ghostscript/fonts-std


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
USE_GMAKE=	Yes
USE_MOTIF=	openmotif
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= --enable-multithreaded \
		 --without-Sgm-library \
		 --without-libpaper-library
CPPFLAGS+=	-I${X11BASE}/include/freetype2

USE_CXX=	Yes
NO_REGRESS=	Yes

post-install:
	@cd ${PREFIX}/bin && \
	  strip pdffonts pdfimages pdfinfo pdftoppm pdftops pdftotext xpdf
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xpdf
	${INSTALL_DATA} ${WRKSRC}/doc/sample-xpdfrc \
		${PREFIX}/share/examples/xpdf/xpdfrc

.include <bsd.port.mk>
