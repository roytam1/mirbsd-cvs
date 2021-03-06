# $MirOS: ports/lang/ghc/Makefile,v 1.6 2008/06/25 15:27:25 bsiegert Exp $
# $OpenBSD: Makefile,v 1.17 2004/05/20 00:08:22 dons Exp $
# 
# Based on Simon Marlow's port script for FreeBSD:
# $FreeBSD: ports/lang/ghc/Makefile,v 1.13 2002/08/22 12:53:38 obraun Exp $
# And on NetBSD's 5.04.3 .hc boot script

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 OpenBSD:*:sparc OpenBSD:*:amd64
 
# The general solution for other architectures will be to boot
# via unregisterised .hc files generated on openbsd-*-i386. See:
#
#  http://haskell.org/ghc/docs/latest/html/building/sec-porting-ghc.html
#
# The best bets are powerpc and alpha. sparc64, mips64 and amd64
# should work. hppa and mips have recently worked. m68k hasn't worked
# for a long time now, and on mac68k at least _ld_ dies with a malloc
# error when linking the ghc binary.
 
# The build process: we build a full GHC from C source. The C source
# needs to be generated once for each arch, for each version of GHC.

COMMENT=			compiler for the functional language Haskell
COMMENT-doc=			documentation for the functional language Haskell

VSN=		6.2.1

DISTNAME=	ghc-${VSN}
CATEGORIES=	lang
HOMEPAGE=	http://www.haskell.org/ghc/

LIB_DEPENDS=	gmp::devel/gmp

MULTI_PACKAGES=	-doc
SUBPACKAGE?=
FULLPKGNAME-doc=ghc-doc-${VSN}-${DASH_VER}
.if defined(PACKAGING) && ${SUBPACKAGE} == "-doc"
PKG_ARCH=	*
.endif

HASKELL=	http://www.haskell.org
MASTER_SITES=	${HASKELL}/ghc/dist/${VSN}/
MASTER_SITES0=	${HASKELL}/ghc/docs/${VSN}/
MASTER_SITES1=	${HASKELL}/definition/
MASTER_SITES2=	ftp://ftp.cse.unsw.edu.au/pub/users/dons/ghc/${VSN}/

DIST_SUBDIR=	ghc-${VSN}
DOC_FILES=	users_guide hslibs building libraries
DOC_FILES1=	haskell98-report
DOC_DIR=	${PREFIX}/share/doc/ghc

DISTFILES=	ghc-${VSN}-src.tar.bz2 \
		${DOC_FILES:C/(.+)/\1.html.tar.gz:0/g} \
		${DOC_FILES1:C/(.+)/\1-html.tar.gz:1/g} \
		ghc-${VSN}-${ARCH}-unknown-openbsd-hc.tar.bz2:2 \
		ghc-regress-${VSN}.tar.bz2:2

# this tarball is the first step in porting to a new architecture
SUPDISTFILES=	ghc-${VSN}-i386-unknown-openbsd-hc.tar.bz2:2  \
		ghc-${VSN}-sparc-unknown-openbsd-hc.tar.bz2:2 \
		ghc-${VSN}-amd64-unknown-openbsd-hc.tar.bz2:2

# datasize around 130M on amd64
VMEM_WARNING=	Yes

USE_GMAKE=	Yes
CONFIGURE_STYLE=gnu dest
CONFIGURE_ENV+=	LOCALBASE="${LOCALBASE}"

# global register variable bug in gcc 3.3.2 screws up amd64. need gcc 3.4
# we bypass it by ignoring all platform dependent tweaks. 2x slowdown.
.if ${MACHINE_ARCH} == "amd64"
CONFIGURE_ARGS+=--enable-hc-boot-unregisterised
.endif

# distrib/hc-build is a wrapper around configure and the
# bootstrap make, with magic flags, vars and control flow
do-configure:
	: nothing here

do-build:
	@(cd ${WRKSRC} ;\
	 ${CONFIGURE_ENV} distrib/hc-build ${CONFIGURE_ARGS})

# note: ghci not in PLIST since it doesnt work yet

FAKE_FLAGS+="stage=1"

post-install:
	${INSTALL_DATA_DIR} ${DOC_DIR}
.for i in ${DOC_FILES:C/(.+)/\1.html.tar.gz/g} \
	  ${DOC_FILES1:C/(.+)/\1-html.tar.gz/g}
	@tar zxf ${FULLDISTDIR}/${i} -C ${DOC_DIR}
.endfor

REGRESS_DEPENDS=::lang/python/2.2
REGRESS_RESULT=	${WRKSRC}/actual.result
REGRESS_FLAGS=	TEST_HC="${WRKSRC}/ghc/compiler/stage1/ghc-inplace"
REGRESS_FLAGS+=	EXTRA_RUNTEST_OPTS="--output-summary=${REGRESS_RESULT}" \
		PYTHON="${LOCALBASE}/bin/python2.2"

# BSD w/o advertising clause
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

.include <bsd.port.mk>
