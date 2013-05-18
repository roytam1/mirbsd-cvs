# $OpenBSD: Makefile,v 1.2 2002/12/29 20:19:10 fgsch Exp $
# $NetBSD: Makefile,v 1.4 2001/11/04 03:28:45 tv Exp $

COMMENT=			.bin/.cue to .iso CD image converter

DISTNAME=	bchunk-1.1.1
CATEGORIES=	sysutils
HOMEPAGE=	http://hes.iki.fi/bchunk/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}

MAKE_FLAGS=	LD=${_PASS_CC:T:Q}

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/bchunk ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/bchunk.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
