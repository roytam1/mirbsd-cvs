# $OpenBSD: Makefile,v 1.2 2004/03/02 23:15:30 naddy Exp $

COMMENT=			displays the phase of the moon in ascii

DISTNAME=		phoon-20030120
CATEGORIES=		astro

HOMEPAGE=		http://www.acme.com/software/phoon/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}
DISTFILES=		phoon_20jan2003.tar.gz

CPPFLAGS+=		-DOS_BSD

WRKDIST=		${WRKDIR}/phoon
NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/phoon ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/phoon.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
