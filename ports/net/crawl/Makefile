# $MirOS: ports/net/crawl/Makefile,v 1.1.7.1 2005/03/18 15:48:03 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/04/07 22:51:03 brad Exp $

BROKEN=			-I/usr/local/include/db

COMMENT=		"small and efficient HTTP crawler"
DISTNAME=		crawl-0.4
CATEGORIES=		net
HOMEPAGE=		http://www.monkey.org/~provos/crawl/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.monkey.org/~provos/
USE_CXX=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--with-db
CONFIGURE_ENV=		CFLAGS="${CFLAGS} -I/usr/local/include/db"

NO_REGRESS=		Yes

post-extract:
	mv ${WRKSRC}/db.h ${WRKSRC}/db-local.h

.include <bsd.port.mk>
