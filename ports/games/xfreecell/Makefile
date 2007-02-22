# $MirOS$
# $NetBSD: Makefile,v 1.13 2007/02/22 19:26:31 wiz Exp $

COMMENT=	Popular freecell card game for X
DISTNAME=	xfreecell-1.0.5b
CATEGORIES=	games
HOMEPAGE=	http://www2.giganet.net/~nakayama/
MASTER_SITES=	${HOMEPAGE}
EXTRACT_SUFX=	.tgz

# historic permission clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_X11=	Yes
USE_GMAKE=	Yes
USE_CXX=	Yes
MAKE_FILE=	makefile

WRKDIST=	${WRKDIR}/xfreecell

MAKE_ENV+=	GMAKE=${GMAKE:Q}

post-extract:
	@print >>${WRKDIST}/makefile

.include <bsd.port.mk>
