# $OpenBSD: Makefile,v 1.5 2003/08/21 14:46:52 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

CATEGORIES=	lang

COMMENT=			Polytechnique Montreal Modula-3
PERMIT_PACKAGE_FTP=Yes
PERMIT_DISTFILES_FTP=Yes
PERMIT_PACKAGE_CDROM=Yes
PERMIT_DISTFILES_CDROM=Yes

VSN=			1.1.15
DISTNAME=		pm3-${VSN}

DISTFILES=		pm3-${VSN}-src.tgz pm3-${VSN}a-OpenBSD_386-boot.tgz:1
PATCHFILES=		pm3-${VSN}-BSD.patch-v1.2.gz:0

EXTRACT_ONLY=pm3-${VSN}-src.tgz

MASTER_SITES= ftp://m3.polymtl.ca/pub/m3/targzip/
MASTER_SITES0= http://people.freebsd.org/~jdp/pm3-for-bsd/
MASTER_SITES1= http://grappa.unix-ag.uni-kl.de/~naddy/

ALL_TARGET=exportall

HOMEPAGE=	http://m3.polymtl.ca/m3/
USE_GMAKE=	Yes
USE_MOTIF=	any

post-extract:
	@cd ${WRKDIST} && \
	    tar zxf ${FULLDISTDIR}/pm3-${VSN}a-OpenBSD_386-boot.tgz

PATCH_DIST_STRIP=-p1

WRKINST=${WRKDIST}/binaries/OpenBSD_386

do-install:
	chown -R ${LIBOWN}:${LIBGRP} ${WRKINST}
	-cd ${PREFIX}/pm3/bin && strip *

M3ARCH=OpenBSD_386
M3OPTIONS=-DPREFIX=${PREFIX} -DLOCALBASE=${LOCALBASE} -DX11BASE=${X11BASE}
MAKE_FLAGS=M3OPTIONS="${M3OPTIONS}"
SUBST_VARS=M3ARCH

NO_REGRESS=	Yes

.include <bsd.port.mk>
