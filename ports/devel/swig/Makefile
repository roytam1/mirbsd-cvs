# $MirOS: ports/devel/swig/Makefile,v 1.6 2008/05/07 22:47:58 tg Exp $
# $OpenBSD: Makefile,v 1.27 2003/12/27 23:23:21 jose Exp $

BROKEN=			distinfo checksum is for 1.3.21, Makefile for 1.3.11

COMMENT=		simplified wrapper and interface generator
COMMENT-examples=	examples for swig

VERSION=	1.3.11

DISTNAME=	swig-${VERSION}
PKGNAME-examples= swig-examples-${VERSION}-0
CATEGORIES=	devel
MASTER_SITES=   ${MASTER_SITE_SOURCEFORGE:=swig/}

HOMEPAGE=       http://www.swig.org/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PYTHON_VER=	2.3
BUILD_DEPENDS=	:python-${PYTHON_VER}*:lang/python/${PYTHON_VER} \
		::lang/tcl/8.4 \
		::lang/guile \
		::lang/ruby

MULTI_PACKAGES=	-examples

WRKDIST=	${WRKDIR}/SWIG-${VERSION}

USE_CXX=	Yes
USE_X11=	Yes
CONFIGURE_STYLE= gnu 
CONFIGURE_ARGS+= --with-tclincl=${LOCALBASE}/include/tcl8.4 \
		 --with-tcllib==${LOCALBASE}/lib/tcl8.4 \
		 --with-guilelib=${LOCALBASE}/lib \
		 --with-python=${LOCALBASE}/bin/python${PYTHON_VER}
MODGNU_RECURSE_DIRS=	${WRKSRC}/Tools

ALL_TARGET=	swig runtime

SWIG_EXAMPLES=	${PREFIX}/share/examples/swig
SWIG_DOCS=	${PREFIX}/share/doc/swig

post-install:
	${INSTALL_DATA_DIR} ${SWIG_EXAMPLES}
	${INSTALL_DATA_DIR} ${SWIG_DOCS}
	cp -R ${WRKSRC}/Examples/* ${SWIG_EXAMPLES}
	cp -R ${WRKSRC}/Doc/* ${SWIG_DOCS}
	
.include <bsd.port.mk>
