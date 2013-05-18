# $OpenBSD: Makefile,v 1.5 2002/12/29 15:10:08 fgsch Exp $

COMMENT=			The Dungeons of Moria

VSN=		5.5.2
DISTNAME=	um${VSN}
PKGNAME=	moria-${VSN}-${DASH_VER}
CATEGORIES=	games
MASTER_SITES=	ftp://ftp.funet.fi/pub/unix/games/moria/source/ \
		ftp://alge.anart.no/pub/games/RPG/moria/
EXTRACT_SUFX=	.tar.Z

HOMEPAGE=	http://www-math.bgsu.edu/~grabine/moria.html


PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=	Yes

WRKDIST=	${WRKDIR}/umoria
WRKSRC=		${WRKDIST}

do-build:
	@cd ${WRKBUILD}; for i in ${WRKSRC}/source/*; do ln -sf $$i; done; \
	 for i in ${WRKSRC}/unix/*; do ln -sf $$i; done; \
	 ln -sf ${WRKSRC}/files; \
	 ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} ${MAKE_FLAGS} PREFIX="${PREFIX}"

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/moria
	@cd ${WRKBUILD}; ${MAKE_PROGRAM} ${FAKE_FLAGS} install

.include <bsd.port.mk>
