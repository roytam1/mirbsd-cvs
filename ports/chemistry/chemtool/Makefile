# $MirOS$

COMMENT=		"drawing tool for chemical structure formulae"

VERSION=		1.6.2
DASH_VER=		
DISTNAME=		chemtool-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
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

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
#AUTOCONF_NEW=		Yes

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/chemtool
	${INSTALL_DATA} ${WRKSRC}/using_chemtool.html ${PREFIX}/share/doc/chemtool

.include <bsd.port.mk>
