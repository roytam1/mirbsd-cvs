# $MirOS$

COMMENT=		"MirBSD Korn Shell"
DISTNAME=		mksh-R23
CATEGORIES=		shells
HOMEPAGE=		http://wiki.mirbsd.de/MirbsdKsh

# MirOS licence; 2-clause UCB-style licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://mirbsd.bsdadvocacy.org/MirOS/distfiles/ \
			http://mirbsd.mirsolutions.de/MirOS/distfiles/
EXTRACT_SUFX=		.cpio.gz

WRKDIST=		${WRKDIR}/mksh
SEPARATE_BUILD=		flavored

do-build:
	cd ${WRKBUILD} && ${SETENV} CC="${CC}" CFLAGS="${CFLAGS:C/ *$//}" \
	    LDFLAGS="${LDFLAGS}" NROFF="${NROFF}" SHELL="${SH}" \
	    ${SH} ${WRKSRC}/Build.sh

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/mksh ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/mksh.cat1 ${PREFIX}/man/cat1/mksh.0

do-regress:
	cd ${WRKSRC} && perl check.pl -s check.t -p ${WRKBUILD}/mksh -C pdksh

.include <bsd.port.mk>
