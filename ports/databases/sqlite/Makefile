# $MirOS: ports/databases/sqlite/Makefile,v 1.1.7.1 2005/03/18 15:44:19 tg Exp $

COMMENT=		"Embedded SQL implementation"
_V=			3.2.1
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

# Public Domain
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--disable-tcl \
			${CONFIGURE_SHARED}

NO_REGRESS=		Yes

.include <bsd.port.mk>
