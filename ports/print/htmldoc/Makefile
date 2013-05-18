# $OpenBSD: Makefile,v 1.13 2002/12/16 17:01:23 wilfried Exp $

BROKEN=			depends on fltk, which is broken

COMMENT=			convert HTML pages to PDF/PS format

VSN=			1.8.23
DISTNAME=		htmldoc-${VSN}
CATEGORIES=     	print www

HOMEPAGE=		http://www.easysw.com/htmldoc

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes

DISTFILES=		${DISTNAME}-source${EXTRACT_SUFX}
MASTER_SITES=		ftp://ftp.easysw.com/pub/htmldoc/${VSN}/ \
			ftp://ftp2.easysw.com/pub/htmldoc/${VSN}/ \
			ftp://ftp.funet.fi/pub/mirrors/ftp.easysw.com/pub/htmldoc/${VSN}/

LIB_DEPENDS=		fltk.1,fltk_images.1::x11/fltk
MODULES+=		graphics/png

CONFIGURE_STYLE=	gnu dest

post-extract:
	@rm -rf ${WRKSRC}/jpeg ${WRKSRC}/png ${WRKSRC}/zlib

NO_REGRESS=		Yes

.include <bsd.port.mk>
