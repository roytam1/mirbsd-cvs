# $MirOS$
# $OpenBSD: Makefile,v 1.5 2003/10/08 17:13:18 sturm Exp $

COMMENT=	"C++ cross-platform GUI toolkit"
DISTNAME=	wxGTK-2.2.9
PKGNAME=	${DISTNAME:L}
CATEGORIES=	x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=wxwindows/}
EXTRACT_SUFX=   .tar.gz
PATCHFILES=	${DISTNAME}-patch1.patch.gz
HOMEPAGE=	http://wesley.informatik.uni-freiburg.de/~wxxt/

LIB_DEPENDS=	gdk.,gtk.::x11/gtk+ \
		glib.,gmodule.,gthread.::devel/glib

CONFIGURE_STYLE=gnu dest
CONFIGURE_ENV=	CXXFLAGS="${CXXFLAGS} -I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

USE_GMAKE=		Yes
USE_CXX=		Yes

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
