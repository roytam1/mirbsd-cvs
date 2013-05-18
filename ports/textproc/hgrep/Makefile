# $OpenBSD: Makefile,v 1.3 2003/01/04 19:09:52 pvalchev Exp $

COMMENT=		"grep wrapper with search highlighting"

DISTNAME=		hgrep-19991004
CATEGORIES=		textproc

HOMEPAGE=		http://www.acme.com/software/hgrep/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}
DISTFILES=		hgrep_04oct1999.tar.gz

NO_REGRESS=		Yes

WRKDIST=	${WRKDIR}/hgrep

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/hgrep ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/hgrep.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
