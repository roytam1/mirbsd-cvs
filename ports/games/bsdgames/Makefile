# $MirOS: ports/games/bsdgames/Makefile,v 1.6 2005/12/28 01:04:55 tg Exp $

COMMENT=		"BSD base system games"
CATEGORIES=		games
CVS_DISTREPO=		anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2005/02/16
CVS_DISTMODS=		src/games
CVS_DISTFILE=		bsdgames
PKGNAME=		${_CVS_DISTF:R}-0
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>
.if !defined(SUDO) || empty(SUDO)
ERRORS+=		"You must use SUDO=sudo."
.endif

PREFIX=			/usr
EXTRA_MAKE_FLAGS=	HOSTCC="${CC}"
EXTRA_FAKE_FLAGS=	MANDIR=${PREFIX}/share/man/cat

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
	${SUDO} rm -rf ${WRKINST}/usr{,/share}/{man,info}
	${SUDO} /usr/sbin/mtree -U -e -d -n -p ${WRKINST} \
	    -f ${FILESDIR}/BSD.games.dist >/dev/null

post-install:
	( cd ${WRKINST}/var && ${SUDO} tar \
	    cf ${WRKINST}/usr/share/games/_tarball.dist games \
	    && rm -rf games )

.include <bsd.port.mk>
