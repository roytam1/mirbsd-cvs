# $MirOS: ports/devel/mirmake/Makefile,v 1.16 2006/10/06 22:20:42 tg Exp $

COMMENT=		portable MirOS make(1) variant
DISTNAME=		mirmake-20061013
CATEGORIES=		devel essentials
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/make/}
EXTRACT_SUFX=		.cpio.gz

# various BSD-style and related licences
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/mirmake
NO_REGRESS=		Yes
MAKE_ENV+=		NROFF=${NROFF:M*:Q}

.if ${OStype} == "Interix"
SED_PLIST+=		| sed -e '/^IFSFU:/s///'
.else
SED_PLIST+=		| sed -e '/^IFSFU:/d'
.endif

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${MKSH} ./Build.sh \
	    ${OStype} ${PREFIX} man/cat mmake \
	    ${MACHINE} ${MACHINE_ARCH} ${MACHINE_OS} \
	    ${MKSH} ${BINOWN}:${BINGRP}

do-install:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} ./Install.sh

.include <bsd.port.mk>

_CIPHERS+=		cksum
