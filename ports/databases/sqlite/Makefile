# $MirOS: ports/databases/sqlite/Makefile,v 1.6 2006/09/14 00:07:59 tg Exp $

COMMENT=		Embedded SQL implementation
_V=			3.3.7
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

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-static \
			--disable-libtool-lock \
			--disable-tcl

NO_REGRESS=		Yes

post-extract:
	cp ${FILESDIR}/regexp.* ${WRKSRC}/src/

.include <bsd.port.mk>
