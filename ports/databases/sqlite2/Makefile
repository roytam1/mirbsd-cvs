# $MirOS: ports/databases/sqlite2/Makefile,v 1.3 2006/02/21 13:37:46 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/03/04 17:49:26 espie Exp $

COMMENT=			Embedded SQL implementation
DISTNAME=		sqlite-2.8.17
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

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

.include <bsd.port.mk>
