# $MirOS: ports/shells/mksh/Makefile,v 1.2 2005/07/08 00:13:53 tg Exp $

COMMENT=		"MirBSD Korn Shell"
DISTNAME=		mksh-R24c
CATEGORIES=		shells
HOMEPAGE=		http://mirbsd.mirsolutions.de/?mksh

# MirOS licence; 2-clause UCB-style licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mksh/}
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
