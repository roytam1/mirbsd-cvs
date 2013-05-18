# $OpenBSD: Makefile,v 1.2 2004/02/16 03:51:47 djm Exp $

COMMENT=	"PF to NetFlow converter"

DISTNAME=	pfflowd-0.4
CATEGORIES=	net
MASTER_SITES=	http://www.mindrot.org/files/pfflowd/

HOMEPAGE=	http://www.mindrot.org/pfflowd.html


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/pfflowd ${PREFIX}/sbin
	${INSTALL_MAN} ${WRKSRC}/pfflowd.8 ${PREFIX}/man/man8

.include <bsd.port.mk>
