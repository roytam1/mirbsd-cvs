# $OpenBSD: Makefile,v 1.2 2004/02/24 14:08:28 couderc Exp $

COMMENT=			Ruby binding to Gdk-imlib

VERSION=	0.34
DISTNAME=	ruby-gnome-all-${VERSION}
PKGNAME=	ruby-gdk-imlib-${VERSION}-0
CATEGORIES=	graphics devel

HOMEPAGE=	http://ruby-gnome.sourceforge.net/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ruby-gnome/}

MODULES=	lang/ruby
LIB_DEPENDS=	gdk_imlib.19::graphics/imlib
RUN_DEPENDS=	:ruby-gtk->=0.31:x11/ruby-gtk

CONFIGURE_STYLE= simple
INSTALL_TARGET=	site-install

USE_X11=	Yes
USE_CXX=	Yes
NO_REGRESS=	Yes

WRKSRC=		${WRKDIST}/gdkimlib
SAMPLE_DIR=	${MODRUBY_EXAMPLEDIR}/ruby-gdk-imlib

post-install:
	${INSTALL_DATA_DIR} ${SAMPLE_DIR}
	${INSTALL_DATA} ${WRKSRC}/sample/* ${SAMPLE_DIR}
	
.include <bsd.port.mk>
