# $MirOS: ports/databases/sqlite/Makefile,v 1.3 2005/07/07 21:18:50 bsiegert Exp $

COMMENT=		"Embedded SQL implementation"
_V=			3.3.5
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}-0
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

# Public Domain
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--disable-tcl \
			${CONFIGURE_SHARED}

NO_REGRESS=		Yes

.include <bsd.port.mk>
