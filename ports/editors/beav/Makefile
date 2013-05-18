# $OpenBSD: Makefile,v 1.21 2002/10/26 00:39:15 naddy Exp $

COMMENT=			binary editor and viewer

DISTNAME=	beav_1.40-15
PKGNAME=	beav-1.40.15-0
CATEGORIES=	editors


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.debian.org/debian/pool/main/b/beav/

WRKDIST=	${WRKDIR}/beav-1.40

NO_REGRESS=	Yes

post-install:
	@perl -i -pe 's:%%PREFIX%%:${TRUEPREFIX}:' ${PREFIX}/man/man1/beav.1

.include <bsd.port.mk>
