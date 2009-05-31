# $MirOS$
# $OpenBSD: Makefile,v 1.2 2007/09/16 02:52:58 merdely Exp $

COMMENT=		generate patchsets from CVS repositories
DISTNAME=		cvsps-2.1
CATEGORIES=		devel
HOMEPAGE=		http://www.cobite.com/cvsps/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.cobite.com/cvsps/
USE_GMAKE=		Yes
NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/cvsps ${PREFIX}/bin
	${INSTALL_MAN} ${WRKBUILD}/cvsps.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
