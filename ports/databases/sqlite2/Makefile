# $MirOS: ports/databases/sqlite2/Makefile,v 1.5 2006/10/06 20:18:38 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/03/04 17:49:26 espie Exp $

COMMENT=		Embedded SQL implementation (obsolete version)
DISTNAME=		sqlite-2.8.17
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

# positively hostile fake-“Public Domain” with contradiction in itself
PERMIT_DISTFILES_CDROM=	hostile PD
PERMIT_DISTFILES_FTP=	hostile PD
PERMIT_PACKAGE_CDROM=	hostile PD
PERMIT_PACKAGE_FTP=	hostile PD

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
USE_GMAKE=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED}

NO_REGRESS=		Yes

.include <bsd.port.mk>
