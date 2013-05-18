# $MirOS: ports/shells/mksh/Makefile,v 1.8 2006/01/01 02:56:00 tg Exp $

COMMENT=		"MirBSD Korn Shell"
DISTNAME=		mksh-R26
PKGNAME=		${DISTNAME:S/-R/-/}-0
CATEGORIES=		shells
HOMEPAGE=		http://www.66h.42h.de/?mksh

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
SEPARATE_BUILD=		flavored

.if !${FLAVOR:L:Mstatic}
BF+=			-d
.endif

do-build:
	cd ${WRKBUILD} && ${SETENV} CC="${CC}" CFLAGS="${CFLAGS:C/ *$//}" \
	    LDFLAGS="${LDFLAGS}" NROFF="${NROFF}" SHELL="${SH}" \
	    ${SH} ${WRKSRC}/Build.sh ${BF}

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/mksh ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/mksh.cat1 ${PREFIX}/man/cat1/mksh.0

do-regress:
	cd ${WRKSRC} && perl check.pl -s check.t -p ${WRKBUILD}/mksh -C pdksh

.include <bsd.port.mk>
