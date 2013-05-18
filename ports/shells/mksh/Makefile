# $MirOS: ports/shells/mksh/Makefile,v 1.16 2006/07/03 12:43:24 tg Exp $

COMMENT=		MirBSD Korn Shell
DISTNAME=		mksh-R28
PKGNAME=		mksh-28.0-0
CATEGORIES=		shells
HOMEPAGE=		http://mirbsd.de/mksh

# MirOS licence; 2-clause UCB-style licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		static
FLAVOR?=

MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mksh/}
EXTRACT_SUFX=		.cpio.gz

WRKDIST=		${WRKDIR}/mksh

.if !${FLAVOR:L:Mstatic}
BF+=			-d
.endif

BSH?=			/bin/sh

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} NROFF=${NROFF:C/ *$//:Q} \
	    SHELL=${BSH:Q} ${BSH} ${WRKSRC}/Build.sh ${BF}

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mksh
	${INSTALL_DATA} ${WRKSRC}/dot.mkshrc ${PREFIX}/share/examples/mksh/
	${INSTALL_PROGRAM} ${WRKBUILD}/mksh ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/mksh.cat1 ${PREFIX}/man/cat1/mksh.0

do-regress:
	${WRKBUILD}/test.sh -v

.include <bsd.port.mk>
