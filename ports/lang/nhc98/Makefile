# $MirOS: ports/lang/nhc98/Makefile,v 1.6 2009/04/18 20:55:19 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/05/16 23:37:58 pvalchev Exp $
# $NetBSD: Makefile,v 1.29 2004/03/26 21:19:53 wiz Exp $

BROKEN=		Segmentation fault (core dumped)

NOT_FOR_PLATFORM=	${LP64_PLATFORMS}

COMMENT=	portable Haskell compiler
VSN=		1.16
DISTNAME=	nhc98-${VSN}
CATEGORIES=	lang
HOMEPAGE=	http://www.haskell.org/nhc98/

MASTER_SITES=	http://www.cs.york.ac.uk/fp/nhc98/
MASTER_SITES0=	ftp://ftp.cse.unsw.edu.au/pub/users/dons/nhc98/${VSN}/

DIST_SUBDIR=	${DISTNAME}
DISTFILES=	nhc98src-${VSN}.tar.gz nhc98-${VSN}-regress.tar.bz2:0

# these are vendor patches
PATCHFILES=	patch-${VSN}-typesyn:0 patch-${VSN}-ghc6:0

USE_GMAKE=	Yes
CONFIGURE_STYLE=simple
CONFIGURE_ARGS+=--installdir=${PREFIX:Q}

# if you use ghc to build nhc98, it will run 2.5x faster than with gcc
# so we relegate the gcc path to archs with no ghc
.if (${OStype} == "OpenBSD") && (${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "sparc")
MODULES+=	lang/ghc
CONFIGURE_ARGS+=--buildwith=ghc
.else
CONFIGURE_ARGS+=--buildwith=${CC:Q}
.endif

EXTRA_XAKE_FLAGS+=	OPT=${CFLAGS:Q}

NO_REGRESS=	we don't have python 2.2 any more, bsiegert@ please update to use 2.5
#REGRESS_DEPENDS+=::lang/python/2.2
#REGRESS_RESULT=	${WRKSRC}/../${DISTNAME}-regress/actual.result
#REGRESS_FLAGS=	TEST_HC=${WRKSRC:Q}/script/nhc98 WAY=normal
#REGRESS_FLAGS+=	EXTRA_RUNTEST_OPTS=--output-summary=${REGRESS_RESULT:Q} \
#		PYTHON=${LOCALBASE:Q}/bin/python2.2

# BSDish
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
