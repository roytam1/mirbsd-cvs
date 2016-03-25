# $MirOS: ports/databases/sqlite2/Makefile,v 1.6 2013/07/03 20:49:29 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/03/04 17:49:26 espie Exp $

COMMENT=		Embedded SQL implementation (obsolete version)
DISTNAME=		sqlite-2.8.17
DASH_VER=		1
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
