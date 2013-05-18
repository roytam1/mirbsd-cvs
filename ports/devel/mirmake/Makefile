# $MirOS: ports/devel/mirmake/Makefile,v 1.37 2008/12/29 20:00:31 tg Exp $
#-
# This port should contain no patches.

COMMENT=		portable MirOS make(1) variant
DISTNAME=		mirmake-20090622
CATEGORIES=		devel essentials
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
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
USE_CCACHE=		No

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${MKSH} Build.sh \
	    ${OStype} ${PREFIX:Q} man/cat mmake \
	    ${MACHINE} ${MACHINE_ARCH} ${MACHINE_OS} \
	    ${MKSH:Q} ${BINOWN:Q}:${BINGRP:Q}

do-install:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} ./Install.sh

.include <bsd.port.mk>

_CIPHERS+=		cksum
MAKE_ENV+=		NROFF=${NROFF:M*:Q}
MAKE_ENV+=		CC=${_ORIG_CC:Q}
MAKE_ENV+=		CFLAGS=${CFLAGS:M*:Q:S${CPPFLAGS:M*:Q}}
