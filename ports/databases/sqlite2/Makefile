# $MirOS: ports/databases/sqlite2/Makefile,v 1.1.7.1 2005/03/18 15:44:19 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/03/04 17:49:26 espie Exp $

COMMENT=	"Embedded SQL implementation"
DISTNAME=	sqlite-2.8.16
CATEGORIES=	databases
HOMEPAGE=	http://www.sqlite.org/
MASTER_SITES=	${HOMEPAGE}

# Public Domain
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
USE_GMAKE=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED}

NO_REGRESS=		Yes

post-extract:
	@rm -f ${WRKSRC}/src/tclsqlite.c.orig

.include <bsd.port.mk>
