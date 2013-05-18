# $MirOS: ports/databases/sqlite/Makefile,v 1.5 2006/05/04 11:41:24 tg Exp $

COMMENT=			Embedded SQL implementation
_V=			3.3.5
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}-1
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

post-extract:
	cp ${FILESDIR}/regexp.* ${WRKSRC}/src/

.include <bsd.port.mk>
