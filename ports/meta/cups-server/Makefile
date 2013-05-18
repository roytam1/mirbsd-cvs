# $MirOS: ports/meta/cups-server/Makefile,v 1.5 2007/04/03 19:44:57 tg Exp $

COMMENT=		meta package for a CUPS server
VERSION=		2.6
PKGNAME=		meta-cups-${VERSION}-${DASH_VER}
CATEGORIES=		meta print
HOMEPAGE=		http://www.cups.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

DISTFILES=		

# meta package, does not contain any files
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

NO_CHECKSUM=		Yes
NO_BUILD=		Yes
PLIST=			/dev/null
PKG_ARCH=		*
USE_CXX=		Yes # depends on cups, which uses CXX

B_R_DEPENDS+=		::print/cups
B_R_DEPENDS+=		::print/ghostscript/esp,cups
B_R_DEPENDS+=		::print/foomatic/filters

do-install:
	# Nothing to do

.include <bsd.port.mk>
