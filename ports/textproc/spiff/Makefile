# $OpenBSD: Makefile,v 1.10 2003/11/15 15:12:55 sturm Exp $

COMMENT=			very flexible diff-like program

DISTNAME=	spiff-1.0
CATEGORIES=	textproc

MASTER_SITES=	http://www.darwinsys.com/freeware/


# custom
PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	"may not modify"
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/spiff ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/spiff.0 ${PREFIX}/man/man1

.include <bsd.port.mk>
