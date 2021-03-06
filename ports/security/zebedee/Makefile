# $OpenBSD: Makefile,v 1.5 2003/01/30 22:39:58 sturm Exp $

COMMENT=			portable, encrypted, compressed tunnel

VERSION=	2.4.1
DISTNAME=	zebedee-${VERSION}
CATEGORIES=	security net

HOMEPAGE=	http://www.winton.org.uk/zebedee/


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=zebedee/} \
		http://www.winton.org.uk/zebedee/

FLAVOURS=	udp_spoof
FLAVOUR?=

LIB_DEPENDS=	bz2::archivers/bzip2
DEFINES_openbsd= -DHAVE_PTHREADS -DBUGGY_FORK_WITH_THREADS
OSLIBS_openbsd=	-pthread

.if ${FLAVOUR:L:Mudp_spoof}
LIB_DEPENDS+=	net::net/libnet
LIBNET_DEFS=	`libnet-config --defines`
DEFINES_openbsd+= -DUSE_UDP_SPOOFING ${LIBNET_DEFS}
LIBNET_LIBS=	`libnet-config --libs`
OSLIBS_openbsd+= ${LIBNET_LIBS}
.endif

NO_REGRESS=	Yes

MAKE_FLAGS+=	CC=${_PASS_CC:T:Q} CFLAGS="${CFLAGS}" OS=openbsd \
		DEFINES_openbsd="${DEFINES_openbsd}" \
		OSLIBS_openbsd="${OSLIBS_openbsd}"

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/zebedee ${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKSRC}/ftpgw.tcl ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/zebedee.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/ftpgw.tcl.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/server.zbd ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/vncviewer.zbd ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/vncserver.zbd ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/server.key ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/server.id ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/client1.key ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/client2.key ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA} ${WRKSRC}/clients.id ${PREFIX}/share/examples/zebedee
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zebedee
	${INSTALL_DATA} ${WRKSRC}/README.txt ${PREFIX}/share/doc/zebedee
	${INSTALL_DATA} ${WRKSRC}/LICENCE.txt ${PREFIX}/share/doc/zebedee
	${INSTALL_DATA} ${WRKSRC}/CHANGES.txt ${PREFIX}/share/doc/zebedee
	${INSTALL_DATA} ${WRKSRC}/zebedee.html ${PREFIX}/share/doc/zebedee
	${INSTALL_DATA} ${WRKSRC}/ftpgw.tcl.html ${PREFIX}/share/doc/zebedee

.include <bsd.port.mk>
