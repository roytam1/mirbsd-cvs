# $OpenBSD: Makefile,v 1.5 2003/08/18 14:56:08 avsm Exp $

# supports 68k, alpha, mips, sparc as well, but not ported yet
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=		TenDRA: advanced BSD-licensed C compiler

VSN=			20030803
DASH_VER=		1
DISTNAME=		tendra-${VSN}
PKGNAME=		tendra-${VSN}-${DASH_VER}
CATEGORIES=		lang

HOMEPAGE=	http://www.tendra.org/

NO_REGRESS=	yes

MASTER_SITES=	ftp://ftp.tendra.org/pub/snapshot/ \
		ftp://ftp.recoil.org/pub/tendra/
EXTRACT_SUFX=	.tar.bz2
WRKDIST=	${WRKDIR}/tendra
ALL_TARGET=

SUBST_VARS+=	OPSYS_VER

# BSDL + Crown Copyright (BSD-like)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

pre-build:
	(cd ${WRKSRC} && make openbsd)

post-install:
	sed s,%%TENDRA%%,${LOCALBASE}/lib/TenDRA/5.0.0/OpenBSD/${OPSYS_VER}/80x86,g \
	< ${FILESDIR}/tcc.sh > ${PREFIX}/bin/tcc

.include <bsd.port.mk>
