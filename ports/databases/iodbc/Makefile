# $MirOS: ports/databases/iodbc/Makefile,v 1.2 2005/07/07 21:18:23 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/01 07:12:39 pvalchev Exp $

COMMENT=			ODBC 2.x driver manager
DISTNAME=	libiodbc-2.50.3
PKGNAME=	iodbc-2.50.3-0
CATEGORIES=	databases
MASTER_SITES=	http://www.iodbc.org/dist/
HOMEPAGE=	http://www.iodbc.org/

# GPL
PERMIT_PACKAGE_CDROM=	yes
PERMIT_PACKAGE_FTP=	yes
PERMIT_DISTFILES_CDROM=	yes
PERMIT_DISTFILES_FTP=	yes

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--with-iodbc-inidir="${SYSCONFDIR}"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/iodbc
	${INSTALL_DATA} ${WRKSRC}/odbc.ini.sample \
	    ${PREFIX}/share/examples/iodbc/odbc.ini
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/examples/iodbc

.include <bsd.port.mk>
