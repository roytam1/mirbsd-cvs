# $OpenBSD: Makefile,v 1.1.1.1 2003/01/06 18:03:44 lebel Exp $

COMMENT=			scan for and send signals to processes

VERSION=	0.3
DISTNAME=	proctools-${VERSION}
CATEGORIES=	sysutils

HOMEPAGE=	http://sourceforge.net/projects/proctools


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=proctools/}

NO_REGRESS=	yes

post-patch:
	@cp ${FILESDIR}/fmt.c ${WRKBUILD}/pgrep

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/pgrep/pgrep ${PREFIX}/bin/
	${INSTALL_PROGRAM} ${WRKBUILD}/pkill/pkill ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/pgrep/pgrep.cat1 ${PREFIX}/man/cat1/pgrep.0
	${INSTALL_MAN} ${WRKBUILD}/pkill/pkill.cat1 ${PREFIX}/man/cat1/pkill.0

.include <bsd.port.mk>
