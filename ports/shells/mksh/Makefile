# $MirOS: ports/shells/mksh/Makefile,v 1.83 2016/11/12 00:25:37 tg Exp $

COMMENT=		MirBSD Korn Shell
DISTNAME=		mksh-R56c
PKGNAME=		${DISTNAME:S/-R/-/}-${DASH_VER}
CATEGORIES=		shells
HOMEPAGE=		http://mirbsd.de/mksh

# The MirOS Licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mksh/}
EXTRACT_SUFX=		.tgz
WRKDIST=		${WRKDIR}/mksh

BSH?=			/bin/sh

do-build:
	rm -rf ${WRKBUILD:Q}/b{l,m} ${WRKBUILD:Q}/lksh.cat1
	mkdir -p ${WRKBUILD:Q}/b{l,m}
	cd ${WRKBUILD:Q}/bm && ${SETENV} ${MAKE_ENV} NROFF=${NROFF:C/ *$//:Q} \
	    SHELL=${BSH:Q} ${BSH} ${WRKSRC:Q}/Build.sh
	cd ${WRKBUILD:Q}/bl && ${SETENV} ${MAKE_ENV} \
	    HAVE_PERSISTENT_HISTORY=0 CPPFLAGS=-DMKSH_BINSHPOSIX \
	    SHELL=${BSH:Q} ${BSH} ${WRKSRC:Q}/Build.sh -r -L
	${NROFF} -mdoc <${WRKSRC:Q}/lksh.1 >${WRKBUILD:Q}/lksh.cat1

do-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/examples/mksh
	${INSTALL_DATA} ${WRKSRC:Q}/dot.mkshrc ${PREFIX:Q}/share/examples/mksh/
	${INSTALL_PROGRAM} ${WRKBUILD:Q}/b?/?ksh ${PREFIX:Q}/bin/
	${INSTALL_MAN} ${WRKBUILD:Q}/bm/mksh.cat1 ${PREFIX:Q}/man/cat1/mksh.0
	${INSTALL_MAN} ${WRKBUILD:Q}/lksh.cat1 ${PREFIX}/man/cat1/lksh.0

# drop -f if you are on a slow machine
REGRESS_FASTBOX=	-f

do-regress:
	${WRKBUILD:Q}/bm/test.sh ${REGRESS_FASTBOX}
	${WRKBUILD:Q}/bl/test.sh ${REGRESS_FASTBOX}

.include <bsd.port.mk>

# this port’s distinfo is shared with OpenBSD ports and NetBSD® pkgsrc®
_CIPHERS+=		cksum
