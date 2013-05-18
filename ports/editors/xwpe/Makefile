# $OpenBSD: Makefile,v 1.19 2002/10/26 00:39:15 naddy Exp $

COMMENT=	"powerful programming editor"

DISTNAME=	xwpe-1.5.22a
CATEGORIES=	editors

MASTER_SITES=	${MASTER_SITE_SUNSITE:=apps/editors/X/} \
		http://www.identicalsoftware.com/xwpe/ 


# License: GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

ALL_TARGET=	xwpe

CONFIGURE_STYLE=gnu
EXTRA_FAKE_FLAGS=	prefix=${WRKINST}${PREFIX}

NO_REGRESS=	Yes

post-install:
	@strip ${PREFIX}/bin/xwpe

.include <bsd.port.mk>
