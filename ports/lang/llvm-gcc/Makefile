# $MirOS: ports/lang/llvm-gcc/Makefile,v 1.2 2008/11/10 20:30:54 tg Exp $

ONLY_FOR_PLATFORM=	Darwin:*:* MirBSD:*:i386

COMMENT=		Low Level Virtual Machine gcc front-end
SVN_DISTREV=		58935
DASH_VER=		1
CATEGORIES=		lang devel
HOMEPAGE=		http://www.llvm.org/

# GNU GPLv?
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

SVN_DISTDIR=		llvm-gcc4.2
SVN_DISTPATH=		http://llvm.org/svn/llvm-project/llvm-gcc-4.2/trunk
MCZ_FETCH=		lzma

USE_CCACHE=		No
USE_CXX=		Yes
USE_GMAKE=		Yes
VMEM_WARNING=		Yes
MODULES+=		converters/libiconv
BUILD_DEPENDS+=		:bison-*:devel/bison
B_R_DEPENDS+=		:llvm-*:lang/llvm
LIB_DEPENDS+=		ltdl::devel/libtool
LIB_DEPENDS+=		gmp:gmp->=4.1:devel/gmp
LIB_DEPENDS+=		mpfr:mpfr->=2.3.2:math/mpfr
SUBST_VARS+=		OStriplet

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ENV+=		LIBTOOL=${LOCALBASE:Q}/bin/libtool \
			M4=/usr/bin/m4
CONFIGURE_ARGS+=	--enable-static \
			${CONFIGURE_SHARED} \
			--disable-libada \
			--enable-libssp \
			--disable-objc-gc \
			--disable-bootstrap \
			--enable-serial-configure \
			--disable-werror \
			--enable-version-specific-runtime-libs \
			--disable-libstdcxx-pch \
			--disable-nls \
			--enable-cxx-flags='-O1 -fno-omit-frame-pointer' \
			--enable-wchar_t \
			--program-prefix=llvm- \
			--enable-llvm=${LOCALBASE:Q} \
			--enable-languages=c,objc,c++,obj-c++,fortran \
			--enable-threads \
			--enable-target-optspace \
			--with-libiconv-prefix=${ICONV_PREFIX:Q} \
			--with-gnu-ld \
			--with-gnu-as \
			--with-system-zlib
EXTRA_XAKE_FLAGS+=	CHECKING_ENABLED=0 \
			ENABLE_OPTIMIZED=1 \
			LIBTOOL=${LOCALBASE:Q}/bin/libtool \
			LLVM_VERSION_INFO=SVN\ r${SVN_DISTREV}-MirPorts-${DASH_VER}
NO_REGRESS=		Yes

.if (${OStype} != "Darwin") && (${MACHINE_ARCH} == "i386")
CONFIGURE_ARGS+=	--with-arch=i486 --with-tune=pentium-mmx
.endif

post-extract:
	-rm -f ${WRKSRC}/GNUmakefile

post-install:
	mv ${PREFIX}/lib/libiberty.a ${PREFIX}/lib/gcc/${OStriplet}/4.2.1/

.include <bsd.port.mk>

_PASS_CC=		${_ORIG_CC}
_PASS_CXX=		${_ORIG_CXX}
