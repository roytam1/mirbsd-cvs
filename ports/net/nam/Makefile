# $MirOS: ports/net/nam/Makefile,v 1.2 2005/07/07 21:24:18 bsiegert Exp $
# $OpenBSD: Makefile,v 1.19 2004/02/25 02:35:17 naddy Exp $
# $FreeBSD: ports/net/nam/Makefile,v 1.3 1999/11/29 03:46:08 steve Exp $

COMMENT=			UCB/LBNL Network Animator

DISTNAME=	nam-src-1.9
PKGNAME=	nam-1.9-0
CATEGORIES=	net

MASTER_SITES= 	ftp://ftp.ee.surrey.ac.uk/pub/Mirrors/ftp.isi.edu/nsnam/ \
		ftp://ftp.isi.edu/nsnam/ \
		http://www.isi.edu/nsnam/dist/

HOMEPAGE=	http://www.isi.edu/nsnam/nam/

# BSD
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	:tclcl->=1.0b13:devel/tclcl

WRKDIST=	${WRKDIR}/${PKGNAME}

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	--with-tcl-ver=8.3 --with-tk-ver=8.3

USE_CXX=	Yes
USE_X11=	Yes

ALL_TARGET=

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/nam ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/nam.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/nam
	${INSTALL_DATA} ${WRKSRC}/ex/* ${PREFIX}/share/examples/nam

.include <bsd.port.mk>
