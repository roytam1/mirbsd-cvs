# $MirOS: ports/lang/otcl/Makefile,v 1.1.7.1 2005/03/18 15:47:46 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/03/13 15:48:54 sturm Exp $
# $FreeBSD: ports/lang/otcl/Makefile,v 1.6 1999/11/28 18:31:28 steve Exp $

COMMENT=			MIT Object Tcl

DISTNAME=	otcl-1.0a8
CATEGORIES=	lang

HOMEPAGE=	http://www.isi.edu/nsnam/otcl/index.html

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.isi.edu/nsnam/dist/

LIB_DEPENDS=    tk83.1:tk->=8.3,<8.4:x11/tk/8.3

USE_CXX=	Yes
USE_X11=	Yes

CONFIGURE_STYLE=gnu dest
CONFIGURE_ARGS+=--includedir=${PREFIX}/include/tcl8.3/generic \
		--with-tcl-ver=8.3 \
		--with-tk-ver=8.3

NO_REGRESS=	Yes

.include <bsd.port.mk>
