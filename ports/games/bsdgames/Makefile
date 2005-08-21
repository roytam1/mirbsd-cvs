# $MirOS: ports/games/bsdgames/Makefile,v 1.2 2005/07/07 21:20:57 bsiegert Exp $

COMMENT=		"BSD base system games"
CATEGORIES=		games
V=			20050215
DISTNAME=		games-${V}
PKGNAME=		bsdgames-${V}-0
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://mirbsd.de/
MASTER_SITES=		${_MASTER_SITE_MIRBSD}
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/games
PREFIX=			/usr
EXTRA_MAKE_FLAGS=	HOSTCC="${CC}"
EXTRA_FAKE_FLAGS=	MANDIR=${LOCALBASE}/man/cat

EXTRA_FORTUNES=		at.linux fvl fvl_vendor martin.piskernig \
			norbert.tretkowski rss thomas.ogrisegg

post-extract:
	cd ${FILESDIR}; cp ${EXTRA_FORTUNES} ${WRKSRC}/fortune/datfiles/

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

pre-build:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} depend

pre-install:
	${SUDO} /usr/sbin/mtree -U -e -d -n -p ${WRKINST} \
	    -f ${FILESDIR}/BSD.games.dist >/dev/null

post-install:
	( cd ${WRKINST}/var && ${SUDO} tar \
	    cf ${WRKINST}/usr/share/games/_tarball.dist games \
	    && rm -rf games )

.include <bsd.port.mk>
