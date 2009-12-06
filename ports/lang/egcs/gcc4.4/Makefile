# $MirOS: ports/lang/egcs/gcc4.4/Makefile,v 1.3 2009/12/06 19:05:02 tg Exp $

# for now...
#ONLY_FOR_PLATFORM+=	Darwin:*:*
ONLY_FOR_PLATFORM+=	MirBSD:*:i386

COMMENT=		GNU Compiler Collection
COMMENT-rtl=		GNU Compiler Collection: Runtime Libraries
CATEGORIES=		lang devel
VSN=			4.4.2

# GNU GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		${MASTER_SITE_GCC:=releases/gcc-${VSN}/}
DISTNAME=		gcc-${VSN}
DISTFILES=		gcc-core-${VSN}${EXTRACT_SUFX}
DISTFILES+=		gcc-objc-${VSN}${EXTRACT_SUFX}
PKGNAME-rtl=		gcc-rtl-${VSN}-${DASH_VER}
NO_REGRESS=		Yes

MULTI_PACKAGES=		-rtl
SUBPACKAGE?=

USE_CCACHE=		No
USE_GMAKE=		Yes
VMEM_WARNING=		Yes
MODULES+=		converters/libiconv
BUILD_DEPENDS+=		:bison-*:devel/bison
LIB_DEPENDS+=		gmp:gmp->=4.1:devel/gmp
LIB_DEPENDS+=		mpfr:mpfr->=2.3.2:math/mpfr
SUBST_VARS+=		OStriplet

MODGNU_RECURSE_DIRS=	${WRKSRC}
MODGNU_RECURSE_DIRS+=	${WRKSRC}/fixincludes
MODGNU_RECURSE_DIRS+=	${WRKSRC}/gcc
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/intl
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libcpp
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libdecnumber
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libgcc
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/libgomp
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libiberty
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/libmudflap
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libobjc
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libssp
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/zlib
AUTOGEN=		${MKSH} ${.CURDIR}/autogen.sh
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--enable-static \
			${CONFIGURE_SHARED} \
			--disable-gold \
			--disable-libada \
			--enable-libssp \
			--disable-objc-gc \
			--disable-bootstrap \
			--enable-serial-configure \
			--with-gmp=${LOCALBASE:Q} \
			--disable-werror \
			--enable-languages=c,objc \
			--enable-threads \
			--disable-sjlj-exceptions \
			--disable-cld \
			--enable-version-specific-runtime-libs \
			--with-gnu-ld \
			--with-gnu-as \
			--with-system-zlib \
			--with-libiconv-prefix=${ICONV_PREFIX:Q} \
			--disable-nls \
			--enable-cpp \
			--disable-libmudflap \
			--disable-libgomp \
			--disable-libstdcxx-pch \
			--enable-cxx-flags='-O1 -fno-omit-frame-pointer' \
			--enable-wchar_t \
			--program-suffix=-${VSN:Q}
EXTRA_XAKE_FLAGS+=	MAKEINFOFLAGS=--no-split
EXTRA_XAKE_FLAGS+=	GNUSYSTEM_AUX_DIR=${GNUSYSTEM_AUX_DIR:Q}
# stupid libgcc tries to install during build
ASUSER_INSTALL_PROGRAM=	${INSTALL} ${INSTALL_COPY} -m ${BINMODE}
ASUSER_INSTALL_DATA=	${INSTALL} ${INSTALL_COPY} -m ${SHAREMODE}
EXTRA_MAKE_FLAGS+=	INSTALL_PROGRAM=${ASUSER_INSTALL_PROGRAM:Q} \
			INSTALL_DATA=${ASUSER_INSTALL_DATA:Q}

.if (${OStype} != "Darwin") && (${MACHINE_ARCH} == "i386")
CONFIGURE_ARGS+=	--with-arch=i486 --with-tune=pentium-mmx
.endif

.if ${OStype} == "MirBSD"
.  if ${OSver:R} < 10
IGNORE+=		"cannot be built: Operating System too old and unsupported"
.  elif ${OSver:R} == 10
.    if ${OSver:E} < 171
IGNORE+=		"cannot be built: Operating System too old and unsupported"
.    endif
.  endif
.endif

post-install:
	cd ${PREFIX}/info && for f in *.info; do \
		mv $$f $${f%.info}-4.4.2.info; \
	done
	mv ${PREFIX}/lib/fpic/libiberty.a \
	    ${PREFIX}/lib/gcc/${OStriplet}/${VSN}/fpic/
	rmdir ${PREFIX}/lib/fpic
	mv ${PREFIX}/lib/libiberty.a ${PREFIX}/lib/gcc/${OStriplet}/${VSN}/

.include <bsd.port.mk>

_PASS_CC=		${_ORIG_CC}
_PASS_CXX=		${_ORIG_CXX}
AUTOCONF_ENV+=		MKSH=${MKSH:Q} PORTSDIR=${PORTSDIR:Q} WRKSRC=${WRKSRC:Q}

.if defined(PACKAGING)
.  if empty(${SUBPACKAGE})
RUN_DEPENDS+=		:gcc-rtl-${VSN}-*:lang/egcs/gcc4.4,-rtl
.  else
B_R_DEPENDS:=
LIB_DEPENDS:=
RUN_DEPENDS:=
.  endif
.endif
