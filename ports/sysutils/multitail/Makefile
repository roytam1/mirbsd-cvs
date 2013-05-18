# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/02/02 01:45:44 naddy Exp $

COMMENT=		multi-window tail(1) utility
DISTNAME=		multitail-3.0.6
CATEGORIES=		sysutils
HOMEPAGE=		http://www.vanheusden.com/multitail/	

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE} \
			${MASTER_SITE_FINK}
EXTRACT_SUFX=		.tgz

NO_REGRESS=	Yes


do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/multitail
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/multitail
	${INSTALL_PROGRAM} ${WRKBUILD}/multitail ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/multitail.1 ${PREFIX}/man/man1
	cd ${WRKSRC} && ${INSTALL_DATA} readme.txt manual.html \
	  ${PREFIX}/share/doc/multitail
	${INSTALL_DATA} ${WRKSRC}/multitail.conf \
	  ${PREFIX}/share/examples/multitail
 
.include <bsd.port.mk>
