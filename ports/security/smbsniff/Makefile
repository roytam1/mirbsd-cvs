# $OpenBSD: Makefile,v 1.4 2002/10/28 17:35:02 naddy Exp $

COMMENT=			sniffer for LanManager environment (m$/samba workstations)
DISTNAME=	smbsniff-0.0.1b
CATEGORIES=	security net

MASTER_SITES=	${HOMEPAGE}/download/

HOMEPAGE=	http://www.hsc.fr/ressources/outils/smbsniff


PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes 
PERMIT_DISTFILES_FTP=	Yes 

WRKDIST=	${WRKDIR}
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKDIST}/smbsniff ${PREFIX}/sbin
	${INSTALL_MAN} ${WRKDIST}/smbsniff.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/smbsniff
	${INSTALL_DATA} ${WRKDIST}/README ${PREFIX}/share/doc/smbsniff

.include <bsd.port.mk>
