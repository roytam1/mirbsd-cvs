# $MirOS: ports/chemistry/chemtool/Makefile,v 1.8 2007/04/11 17:05:29 bsiegert Exp $

COMMENT=		drawing tool for chemical structure formulae

VERSION=		1.6.10
DISTNAME=		chemtool-${VERSION}
CATEGORIES=		misc graphics

HOMEPAGE=		http://ruby.chemie.uni-freiburg.de/~martin/chemtool/
MASTER_SITES=		${HOMEPAGE}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes


RUN_DEPENDS=		::print/transfig
LIB_DEPENDS=		atk-1.0.0.0::devel/atk \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	gnu
MODULES=		devel/gettext devel/pkgconfig

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/chemtool
	${INSTALL_DATA} ${WRKSRC}/using_chemtool.html ${PREFIX}/share/doc/chemtool

.include <bsd.port.mk>
