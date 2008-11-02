# $MirOS$

BROKEN=			porting in progress

COMMENT=		Low Level Virtual Machine compiler infrastructure
DISTNAME=		llvm-2.4
SVN_DISTDIR0=		llvm-clang
SVN_DISTREV0=		58548
PKGNAME=		llvm-2.4rc2-${DASH_VER}
CATEGORIES=		lang devel
HOMEPAGE=		http://clang.llvm.org/

# 3-clause BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://llvm.org/prereleases/2.4/
SVN_DISTPATH0=		http://llvm.org/svn/llvm-project/cfe/trunk

USE_CXX=		Yes
USE_GMAKE=		Yes
BUILD_DEPENDS+=		:bison-*:devel/bison
LIB_DEPENDS+=		ltdl::devel/libtool

MODGNU_RECURSE_DIRS=	${WRKSRC}/autoconf
AUTOGEN=		${SHELL} ${FILESDIR}/autogen.sh
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
MODSIMPLE_given_INSTALL=${INSTALL} -c
CONFIGURE_ENV+=		ac_cv_path_GRAPHVIZ="echo Graphviz" \
			ac_cv_path_DOT="echo dot" \
			ac_cv_path_GV="echo gv" \
			ac_cv_path_DOTTY="echo dotty" \
			ac_cv_path_BZIP2= \
			ac_cv_path_DOXYGEN= \
			ac_cv_path_GROFF= \
			ac_cv_path_ZIP= \
			YACC="bison -y"
CONFIGURE_ARGS+=	--enable-optimized \
			--disable-assertions \
			--disable-expensive-checks \
			--enable-jit \
			--disable-doxygen \
			--enable-targets=all \
			--disable-cbe-printf-a \
			--enable-bindings=none \
			--disable-ltdl-install \
			${CONFIGURE_SHARED} \
			--enable-static
EXTRA_XAKE_FLAGS+=	VERBOSE=1 \
			DISABLE_AUTO_DEPENDENCIES=1

post-extract:
	-rm -rf ${WRKSRC}/projects/sample
	mv ${WRKDIR}/llvm-clang ${WRKSRC}/tools/clang

pre-build:
	# What the fuck?!
	cd ${WRKBUILD} && rm -f mklib && ln -s libtool mklib

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/llvm/clang
	cd ${WRKSRC}/tools/clang/utils && ${INSTALL_SCRIPT} scan-build \
	    CheckBuiltinMacros.sh FindSpecRefs ccc ccc-analyzer ubiviz \
	    ${PREFIX}/share/llvm/clang/
	cd ${WRKSRC}/tools/clang/utils && ${INSTALL_DATA} scanview.css \
	    sorttable.js ${PREFIX}/share/llvm/clang/
	cd ${PREFIX}/bin && \
	    ln -s ../share/llvm/clang/ccc . && \
	    ln -s ../share/llvm/clang/scan-build .
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/llvm/clang-www
	cd ${WRKSRC}/tools/clang/www && \
	    pax -rw . ${PREFIX}/share/doc/llvm/clang-www/

.include <bsd.port.mk>
