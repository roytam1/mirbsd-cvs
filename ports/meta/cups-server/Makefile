# $MirOS: ports/meta/cups-server/Makefile,v 1.1 2006/11/09 18:18:57 bsiegert Exp $

COMMENT=		meta package for a CUPS server
VERSION=		2.6
DASH_VER=		-0
PKGNAME=		meta-cups-${VERSION}${DASH_VER}
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
PKG_ARCH=		*

RUN_DEPENDS+=		::print/cups
RUN_DEPENDS+=		::print/ghostscript/esp,cups
RUN_DEPENDS+=		::print/foomatic/filters

BUILD_DEPENDS+=		${RUN_DEPENDS}

do-install:
	# Nothing to do

.include <bsd.port.mk>
