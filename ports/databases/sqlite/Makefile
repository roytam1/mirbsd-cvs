# $MirOS$

COMMENT=		"Embedded SQL implementation"
_V=			3.0.8
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
WRKDIST=		${WRKDIR}/sqlite
CONFIGURE_ARGS=		--without-tcl \
			${CONFIGURE_SHARED}

NO_REGRESS=		Yes

.include <bsd.port.mk>
