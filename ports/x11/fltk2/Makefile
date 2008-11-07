# $MirOS: ports/x11/fltk2/Makefile,v 1.1 2008/11/04 21:00:08 bsiegert Exp $

COMMENT=		fast, lightweight toolkit, version 2

VERSION=		2.0
DASH_VER=		1
PKGNAME=		fltk2-${VERSION}.${SVN_DISTREV}-${DASH_VER}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.fltk.org/

SVN_DISTPATH=		http://svn.easysw.com/public/fltk/fltk/trunk/
SVN_DISTDIR=		fltk
SVN_DISTREV=		6496

# GPLv2, with
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		graphics/png
LIB_DEPENDS+=		jpeg::graphics/jpeg

USE_X11=		Yes
USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf no-autoheader
AUTOCONF_NEW=		Yes
NO_REGRESS=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-cairo
CONFIGURE_ARGS+=	--disable-xft

.include <bsd.port.mk>
