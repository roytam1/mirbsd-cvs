# $OpenBSD: Makefile,v 1.19 2003/06/18 14:19:09 brad Exp $

COMMENT=			Cistron RADIUS server

VERSION=	1.6.6
DISTNAME=	radiusd-cistron-${VERSION}
PKGNAME=	${DISTNAME}-1
CATEGORIES=	net
MASTER_SITES=	ftp://ftp.radius.cistron.nl/pub/radius/ \
		ftp://ftp.freeradius.org/pub/radius/ \
		ftp://ftp.mma.com.br/pub/cistron-radius/

HOMEPAGE=	http://www.radius.cistron.nl/

RUN_DEPENDS=	::net/p5-Net-Telnet \
		::net/p5-SNMP_Session


PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes 
PERMIT_DISTFILES_FTP=	Yes 

WRKSRC=		${WRKDIST}/src
MAKE_FILE=	Makefile.BSD
MAKE_FLAGS+=	CC=${_PASS_CC:T:Q} LCRYPT="" DBM="-DUSE_DB1" DBMLIBS=""
CPPFLAGS+=	-DNOSHADOW -DUSE_SYSLOG
FAKE_FLAGS+=	BINDIR='${WRKINST}${PREFIX}/bin' \
		SBINDIR='${WRKINST}${PREFIX}/sbin' \
		MANDIR='${WRKINST}${PREFIX}/man' \
		RADIUS_DIR='${WRKINST}${PREFIX}/share/examples/radiusd-cistron'
NO_REGRESS=	Yes

post-install:
	${INSTALL_MAN} ${WRKDIST}/doc/clients.5rad ${PREFIX}/man/man5/clients.5
	${INSTALL_MAN} ${WRKDIST}/doc/naslist.5rad ${PREFIX}/man/man5/naslist.5
	${INSTALL_MAN} ${WRKDIST}/doc/builddbm.8rad \
		${PREFIX}/man/man8/builddbm.8
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/radiusd-cistron
	@for file in ${WRKDIST}/doc/README* ; do \
		${INSTALL_DATA} $$file ${PREFIX}/share/doc/radiusd-cistron; \
	done

.include <bsd.port.mk>
