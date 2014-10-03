# $MirOS: ports/shells/mksh/Makefile,v 1.72 2014/09/03 19:55:51 tg Exp $

COMMENT=		MirBSD Korn Shell
DISTNAME=		mksh-R50c
PKGNAME=		${DISTNAME:S/-R/-/}-${DASH_VER}
CATEGORIES=		shells
HOMEPAGE=		http://mirbsd.de/mksh

# MirOS licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mksh/}
EXTRACT_SUFX=		.tgz
WRKDIST=		${WRKDIR}/mksh

BSH?=			/bin/sh

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} NROFF=${NROFF:C/ *$//:Q} \
	    SHELL=${BSH:Q} ${BSH} ${WRKSRC}/Build.sh

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mksh
	${INSTALL_DATA} ${WRKSRC}/dot.mkshrc ${PREFIX}/share/examples/mksh/
	${INSTALL_PROGRAM} ${WRKBUILD}/mksh ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/mksh.cat1 ${PREFIX}/man/cat1/mksh.0

do-regress:
	# drop -f if you are on a slow machine
	${WRKBUILD}/test.sh -f

.include <bsd.port.mk>

# this port’s distinfo is shared with OpenBSD ports and NetBSD® pkgsrc®
_CIPHERS+=		cksum
