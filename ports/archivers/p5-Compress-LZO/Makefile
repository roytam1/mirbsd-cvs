# $OpenBSD: Makefile,v 1.17 2004/01/17 15:58:06 naddy Exp $

BROKEN=			archivers/lzo too new

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			interface to lzo compression library

DISTNAME=	perl-lzo-1.08
PKGNAME=	p5-Compress-LZO-1.08-0
CATEGORIES=	archivers perl5
MASTER_SITES=	http://www.oberhumer.com/opensource/lzo/download/

HOMEPAGE=	http://www.oberhumer.com/opensource/lzo/

LIB_DEPENDS=	lzo.1::archivers/lzo


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

WRKDIST=	${WRKDIR}/Compress-LZO-1.08

.include <bsd.port.mk>
