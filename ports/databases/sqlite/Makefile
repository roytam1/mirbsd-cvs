# $MirOS: ports/databases/sqlite/Makefile,v 1.8 2007/02/22 22:57:44 tg Exp $

COMMENT=		Embedded SQL implementation
_V=			3.3.17
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}-${DASH_VER}
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
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-static \
			--disable-tcl

NO_REGRESS=		Yes

post-extract:
	cp ${FILESDIR}/regexp.* ${WRKSRC}/src/

.include <bsd.port.mk>
