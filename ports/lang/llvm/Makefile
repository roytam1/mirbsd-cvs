# $MirOS: ports/lang/llvm/Makefile,v 1.7 2008/11/10 01:01:32 tg Exp $

COMMENT=		Low Level Virtual Machine compiler infrastructure
SVN_DISTREV=		58935
CATEGORIES=		lang devel
HOMEPAGE=		http://clang.llvm.org/

# 3-clause BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

.if ${OStype} == "MirBSD"
.  if ${OSver:R} < 10
IGNORE+=		"cannot be built: Operating System too old and unsupported"
.  elif ${OSver:R} == 10
.    if ${OSver:E} < 163
IGNORE+=		"is not for you: You're not fit enough for that much disgusting C++ junk. Go away"
.    endif
.  endif
.endif

SVN_DISTDIR=		llvm
SVN_DISTPATH=		http://llvm.org/svn/llvm-project/llvm/trunk
SVN_DISTDIR0=		llvm/tools/clang
SVN_DISTREV0=		${SVN_DISTREV}
SVN_DISTPATH0=		http://llvm.org/svn/llvm-project/cfe/trunk
MCZ_FETCH=		lzma

USE_CXX=		Yes
USE_GMAKE=		Yes
BUILD_DEPENDS+=		:bison-*:devel/bison
BUILD_DEPENDS+=		:groff-*-!no_x11:textproc/groff
LIB_DEPENDS+=		ltdl::devel/libtool

MODGNU_RECURSE_DIRS=	${WRKSRC}/autoconf
AUTOGEN=		${SHELL} ${FILESDIR}/autogen.sh
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
MODSIMPLE_USE_INSTALL=	${INSTALL} -c
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
CPPFLAGS+=		-DLLVM_VERSION_INFO_SVN=\"r${SVN_DISTREV}-MirPorts-${DASH_VER}\"

post-extract:
	-rm -rf ${WRKSRC}/projects/sample

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
	chmod 0600 ${PREFIX}/bin/gcc{as,ld}
	for file in ${PREFIX}/bin/gcc{as,ld}; do \
		print ',g'${WRKINST:Q}'s///\nwq' | ed -s $$file; \
	done
	chmod ${BINMODE} ${PREFIX}/bin/gcc{as,ld}

.include <bsd.port.mk>
