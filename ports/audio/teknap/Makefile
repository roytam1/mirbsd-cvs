# $MirOS$
# $OpenBSD: Makefile,v 1.10 2002/12/29 19:29:57 fgsch Exp $

COMMENT=	console napster client

VERSION=	1.3g
DASH_VER=	1
DISTNAME=	TekNap-${VERSION}
PKGNAME=	teknap-${VERSION}-${DASH_VER}
CATEGORIES=	audio
MASTER_SITES=	ftp://ftp.teknap.com/pub/TekNap/

HOMEPAGE=	http://www.TekNap.com/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE=	gnu dest

NO_REGRESS=		Yes

WRKDIST=	${WRKDIR}/TekNap

.include <bsd.port.mk>
