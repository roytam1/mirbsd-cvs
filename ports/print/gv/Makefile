# $MirOS: ports/print/gv/Makefile,v 1.5 2007/02/26 19:27:21 bsiegert Exp $
# $OpenBSD: Makefile,v 1.23 2004/01/04 21:32:18 espie Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	PostScript and PDF previewer

DISTNAME=	gv-3.5.8
DASH_VER=	5
CATEGORIES=	print

HOMEPAGE=	http://wwwthep.physik.uni-mainz.de/~plass/gv/
MASTER_SITES=	ftp://ftpthep.physik.uni-mainz.de/pub/gv/unix/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	Xaw3d.6.1::x11/Xaw3d
RUN_DEPENDS=	:ghostscript-*:print/ghostscript/artifex

CONFIGURE_STYLE=	imake
USE_X11=		Yes

NO_REGRESS=	Yes

INSTALL_TARGET=	install install.man install.doc

post-extract:
	cd ${WRKSRC}/source && mv signal.h gvsignal.h

pre-configure:
	cd ${WRKSRC}/source && ./inc_2lit

post-install:
	${INSTALL_MAN} ${WRKSRC}/source/gv.0 ${PREFIX}/man/cat1


.include <bsd.port.mk>
