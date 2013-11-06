# $MirOS: ports/devel/argp-standalone/Makefile,v 1.1 2013/11/06 19:08:43 tg Exp $
# $OpenBSD: Makefile,v 1.4 2013/03/11 10:50:00 espie Exp $

COMMENT=		Standalone version of arguments parsing functions from GLIBC
DISTNAME=		argp-standalone-1.3
CATEGORIES=		devel

# GNU LGPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.lysator.liu.se/~nisse/misc/
SEPARATE_BUILD=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-shared

do-install:
	${INSTALL_DATA} ${WRKBUILD}/libargp.a ${PREFIX}/lib/
	${INSTALL_DATA} ${WRKSRC}/argp.h ${PREFIX}/include/

.include <bsd.port.mk>
