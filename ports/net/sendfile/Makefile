# $MirOS: ports/net/sendfile/Makefile,v 1.1.7.1 2005/03/18 15:49:04 tg Exp $

COMMENT=			tool for asynchronous sending of files
VER=			20010424
DISTNAME=		sendfile-${VER}
WRKDIST=        	${WRKDIR}/sendfile-2.1a
CATEGORIES=		net
HOMEPAGE=		http://www.belwue.de/projekte/saft/sendfile-us.html

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.belwue.de/pub/unix/sendfile/current/

NO_REGRESS=		Yes

post-extract:
	cp ../../infrastructure/db/config.guess ${WRKSRC}/develop

do-install:	
	${INSTALL_PROGRAM} ${WRKSRC}/src/sendfile ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/sendmsg ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/receive ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/fetchfile ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/utf7encode ${PREFIX}/bin
	@cd ${PREFIX}/bin && ln -fs utf7encode utf7decode
	${INSTALL_PROGRAM} ${WRKSRC}/src/wlock ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/src/sendfiled ${PREFIX}/libexec
	${INSTALL_MAN} ${WRKSRC}/doc/sendfile.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/fetchfile.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/receive.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/sendmsg.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/wlock.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/utf7encode.1 ${PREFIX}/man/man1
	@cd ${PREFIX}/man/man1 && ln -fs utf7encode.1 utf7decode.1
	${INSTALL_MAN} ${WRKSRC}/doc/sendfiled.8 ${PREFIX}/man/man8
	${INSTALL_SCRIPT} ${WRKSRC}/etc/sfconf ${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKSRC}/etc/sfdconf ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/sendfile
	${INSTALL_DATA} ${WRKSRC}/etc/sendfile.cf ${PREFIX}/share/examples/sendfile
	${INSTALL_DATA} ${WRKSRC}/etc/sendfile.deny ${PREFIX}/share/examples/sendfile

.include <bsd.port.mk>
