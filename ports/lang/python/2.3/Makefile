# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/04/06 02:39:23 brad Exp $

VERSION=		2.3
PATCHLEVEL=		.4
PKG_PATCHLEVEL=

COMMENT-bsddb=		"Berkeley db module for Python"
FULLPKGNAME-bsddb=	python-bsddb-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS=		--enable-ipv6
AUTOCONF_NEW=		Yes

LIB_DEPENDS+=		bz2::archivers/bzip2

FLAVORS+=		no_bsddb

.include <bsd.port.mk>
