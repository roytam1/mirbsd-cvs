# $MirOS: ports/games/bsdgames/Makefile,v 1.23 2015/10/13 18:38:46 tg Exp $

COMMENT=		BSD base system games
CATEGORIES=		games
DASH_VER=		4
MCZ_FETCH=		Yes
CVS_DISTREPO=		:ext:anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2007/02/22
CVS_DISTMODS=		src/games
CVS_DISTFILE=		bsdgames
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>
.if !defined(SUDO) || empty(SUDO)
IGNORE+=		"requires use of SUDO=sudo"
.endif

PREFIX=			/usr
BINGRP=			games
EXTRA_MAKE_FLAGS=	HOSTCC=${_PASS_CC:T:Q}
EXTRA_FAKE_FLAGS=	MANDIR=${PREFIX:Q}/share/man/cat
.ifdef MAN_ONLY
EXTRA_XAKE_FLAGS+=	BSD_SUBDIR_MK_MANRECURSE=1
.endif

EXTRA_FORTUNES=		alexander.griesser alexander.talos andreas.krennmair \
			at.linux at.statistik de.misc en.misc farber fh-brs \
			fvl fvl_vendor larry.wall martin.piskernig netbsd \
			netbsd-o netbsd-tips norbert.tretkowski \
			rainer.weikusat rss thomas.ogrisegg tretkowski \
			unamerican-o
.if (${OStype} == "Interix") || (${OStype} == "OpenBSD")
FORTUNE_COPY=		cat	# crippled OS
.else
MODULES+=		converters/libiconv
FORTUNE_COPY=		iconv -f iso-8859-1 -t utf-8
.endif

post-extract:
.for _i in ${EXTRA_FORTUNES}
	${FORTUNE_COPY} <${FILESDIR}/${_i} >${WRKSRC}/fortune/datfiles/${_i}
.endfor

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

.ifndef MAN_ONLY
pre-build:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} depend
.endif

pre-install:
	${SUDO} rm -rf ${WRKINST}/usr{,/share}/{man,info}
	${SUDO} /usr/sbin/mtree -U -e -d -n -p ${WRKINST} \
	    -f ${FILESDIR}/BSD.games.dist
.ifdef MAN_ONLY
	mkdir -p ${WRKINST}/usr/share/man/cat8
.endif

.ifndef MAN_ONLY
post-install:
	cd ${WRKINST}/var && ${SUDO} tar cf \
	    ${WRKINST}/usr/share/games/_tarball.dist games && \
	    rm -rf games
.endif

.include <bsd.port.mk>
