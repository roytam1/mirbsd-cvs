# $MirOS$

BROKEN=			autohell trouble...

# for now...
#ONLY_FOR_PLATFORM+=	Darwin:*:*
ONLY_FOR_PLATFORM+=	MirBSD:*:i386

COMMENT=		GNU Compiler Collection
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
NO_REGRESS=		Yes

USE_CCACHE=		No
USE_GMAKE=		Yes
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
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libgomp
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libiberty
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libmudflap
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
			--disable-werror \
			--enable-languages=c,objc \
			--disable-sjlj-exceptions \
			--disable-cld \
			--enable-version-specific-runtime-libs \
			--with-gnu-ld \
			--with-gnu-as \
			--with-libiconv-prefix=${ICONV_PREFIX:Q} \
			--disable-nls \
			--enable-cpp \
			--disable-libmudflap \
			--disable-libgomp \
			--disable-libstdcxx-pch \
			--enable-cxx-flags='-O1 -fno-omit-frame-pointer' \
			--enable-wchar_t \
			--with-system-zlib

.if (${OStype} != "Darwin") && (${MACHINE_ARCH} == "i386")
CONFIGURE_ARGS+=	--with-arch=i486 --with-tune=pentium-mmx
.endif

.if ${OStype} == "MirBSD"
.  if ${OSver:R} < 10
CONFIGURE_ARGS+=	--enable-cld
.  elif ${OSver:R} == 10
.    if ${OSver:E} < 160
CONFIGURE_ARGS+=	--enable-cld
.    endif
.  endif
.else
CONFIGURE_ARGS+=	--enable-cld
.endif

.include <bsd.port.mk>

_PASS_CC=		${_ORIG_CC}
_PASS_CXX=		${_ORIG_CXX}
AUTOCONF_ENV+=		MKSH=${MKSH:Q} PORTSDIR=${PORTSDIR:Q}
AUTOCONF_ENV+=		MODGNU_RECURSE_DIRS=${MODGNU_RECURSE_DIRS:Q}
