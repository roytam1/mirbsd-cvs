# $OpenBSD: Makefile,v 1.6 2004/02/07 06:38:12 brad Exp $

COMMENT=			Ftp daemon which aims to be secure

VERSION=		1.2.1
DISTNAME=		vsftpd-${VERSION}
CATEGORIES=		net

HOMEPAGE=		http://vsftpd.beasts.org/


# GPL2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://vsftpd.beasts.org/users/cevans/

ALL_TARGET=		vsftpd

MAKE_FLAGS=		CC=${_PASS_CC:T:Q} CFLAGS=${CFLAGS:Q}" -Wall -W -Wshadow"

SAMPLEDIR=		${PREFIX}/share/examples/vsftpd
NO_REGRESS=		Yes

do-configure:
	@perl -pi -e "s,%%SYSCONFDIR%%,${SYSCONFDIR}," ${WRKSRC}/defs.h

do-install:
	${INSTALL} ${WRKSRC}/vsftpd ${PREFIX}/sbin/
	${INSTALL_MAN} ${WRKSRC}/vsftpd.8 ${PREFIX}/man/man8
	${INSTALL_MAN} ${WRKSRC}/vsftpd.conf.5 ${PREFIX}/man/man5
	${INSTALL_DATA_DIR} ${SAMPLEDIR}
	@cp -r ${WRKSRC}/EXAMPLE/* ${SAMPLEDIR}
	${INSTALL_DATA} ${WRKSRC}/vsftpd.conf ${SAMPLEDIR}

.include <bsd.port.mk>
