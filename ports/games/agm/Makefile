# $OpenBSD: Makefile,v 1.16 2002/12/23 08:05:51 pvalchev Exp $
#

COMMENT=			AnaGram search utility

DISTNAME=		agm-1.3.1
CATEGORIES=		games

PERMIT_PACKAGE_CDROM=	"no license available"
PERMIT_PACKAGE_FTP=	"no license available"
PERMIT_DISTFILES_CDROM=	"no license available"
PERMIT_DISTFILES_FTP=	"no license available"

MASTER_SITES=		${MASTER_SITE_SUNSITE:=games/amusements/}

NO_REGRESS=		Yes

do-install:
	@ ${INSTALL_PROGRAM} ${WRKSRC}/agm ${PREFIX}/bin
	@ ${INSTALL_MAN} ${WRKSRC}/agm.6 ${PREFIX}/man/man6

.include <bsd.port.mk>
