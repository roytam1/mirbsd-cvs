# $MirOS$
# $OpenBSD: Makefile,v 1.21 2002/10/27 18:29:15 naddy Exp $

BROKEN=		patches do not apply

COMMENT=	from Kernighan & Pike: High Order Calculator

DISTNAME=	hoc
PKGNAME=	hoc-1.1-0
CATEGORIES=	math

MASTER_SITES=	http://cm.bell-labs.com/cm/cs/who/bwk/
EXTRACT_SUFX=	.sh

HOMEPAGE=	http://cm.bell-labs.com/cm/cs/who/bwk/

# License is included in the distfile: "Permission to use, copy, 
# modify, and distribute this software... for any purpose and without
# fee.. provided that the copyright notice appear in all copies..."
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

ALL_TARGET=	hoc
MAKE_FILE=	makefile

WRKDIST=	${WRKDIR}

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/hoc ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/hoc.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
