# $MirOS: ports/net/jftpgw/Makefile,v 1.2 2006/02/09 09:36:09 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/08/11 18:45:42 brad Exp $

COMMENT=			FTP proxy

DISTNAME=	jftpgw-0.13.5
CATEGORIES=	net
MASTER_SITES=	http://www.mcknight.de/jftpgw/

HOMEPAGE=	http://www.mcknight.de/jftpgw/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+= --enable-crypt \
		 --enable-libwrap \
		 --with-confpath="${SYSCONFDIR}" \
		 --with-logpath="/var/log"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/jftpgw
	${INSTALL_DATA} ${WRKINST}${SYSCONFDIR}/jftpgw.conf \
		${PREFIX}/share/examples/jftpgw

.include <bsd.port.mk>
