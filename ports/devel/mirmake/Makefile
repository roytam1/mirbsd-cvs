# $MirOS: ports/devel/mirmake/Makefile,v 1.34 2008/04/07 00:42:41 tg Exp $
#-
# This port should contain no patches.

COMMENT=		portable MirOS make(1) variant
DISTNAME=		mirmake-20080411
CATEGORIES=		devel essentials
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/make/}
EXTRACT_SUFX=		.cpio.gz

# various BSD-style and related licences
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# never ever set a flavour from the list below manually!
FLAVOURS=		wrapper setup

WRKDIST=		${WRKDIR}/mirmake
NO_REGRESS=		Yes
MAKE_ENV+=		NROFF=${NROFF:M*:Q}

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} \
	    CFLAGS=${CFLAGS:M*:Q:S${CPPFLAGS:M*:Q}} \
	    ${MKSH} ./Build.sh \
	    ${OStype} ${PREFIX} man/cat mmake \
	    ${MACHINE} ${MACHINE_ARCH} ${MACHINE_OS} \
	    ${MKSH} ${BINOWN}:${BINGRP}

do-install:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} ./Install.sh

.include <bsd.port.mk>

_CIPHERS+=		cksum
