# $MirOS: ports/lang/egcs/gcc4.4/Makefile,v 1.12 2014/05/29 22:33:21 tg Exp $

ONLY_FOR_PLATFORM+=	MirBSD:10.181:i386

COMMENT=		GNU Compiler Collection
COMMENT-rtl=		GNU Compiler Collection: Runtime Libraries
CATEGORIES=		lang devel
VSN=			4.4.7
HOMEPAGE=		http://gcc.gnu.org/

# GNU GPLv3+, GFDLv1.2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

VSS=			${VSN:R}
MASTER_SITES=		${MASTER_SITE_GCC:=releases/gcc-${VSN}/}
DISTNAME=		gcc-${VSN}
EXTRACT_SUFX=		.tar.bz2
DISTFILES=		gcc-core-${VSN}${EXTRACT_SUFX}
DISTFILES+=		gcc-g++-${VSN}${EXTRACT_SUFX}
PKGNAME-rtl=		gcc-rtl-${VSN}-${DASH_VER}
NO_REGRESS=		Yes

MULTI_PACKAGES=		-rtl
SUBPACKAGE?=

USE_CCACHE=		No
USE_CXX=		No
USE_GMAKE=		Yes
VMEM_WARNING=		Yes
.if defined(PACKAGING) && (${SUBPACKAGE} == "-rtl")
MODULES=
.else
MODULES+=		converters/libiconv
LIB_DEPENDS+=		gmp:gmp->=4.1:devel/gmp
LIB_DEPENDS+=		mpfr:mpfr->=2.3.2:math/mpfr
.  if ${SUBPACKAGE} != "-rtl"
RUN_DEPENDS+=		:gcc-rtl-${VSN}-*:lang/egcs/gcc${VSS},-rtl
.  endif
.endif

SUBST_VARS+=		OStriplet
SUBST_VARS+=		VSN VSS

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
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/libobjc
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/libssp
MODGNU_RECURSE_DIRS+=	${WRKSRC}/libstdc++-v3
#MODGNU_RECURSE_DIRS+=	${WRKSRC}/zlib
AUTOGEN=		${MKSH} ${.CURDIR}/autogen.sh
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--enable-static \
			${CONFIGURE_SHARED} \
			--disable-gold \
			--disable-libada \
			--disable-libssp \
			--disable-libgomp \
			--disable-libmudflap \
			--disable-objc-gc \
			--enable-bootstrap \
			--enable-serial-configure \
			--disable-werror \
			--with-mpfr=${LOCALBASE:Q} \
			--with-gmp=${LOCALBASE:Q} \
			--enable-threads \
			--disable-tls \
			--enable-languages=c,c++ \
			--disable-sjlj-exceptions \
			--disable-cld \
			--enable-version-specific-runtime-libs \
			--with-gnu-ld \
			--with-gnu-as \
			--with-libiconv-prefix=${ICONV_PREFIX:Q} \
			--with-system-zlib \
			--disable-libstdcxx-pch \
			--disable-nls \
			--enable-wchar_t \
			--enable-cxx-flags='-O1 -fno-omit-frame-pointer' \
			--program-suffix=-${VSS:Q}
FORCE_STAGE1_CFLAGS=	${CPPFLAGS} ${CFLAGS}
CONFIGURE_ENV+=		FORCE_STAGE1_CFLAGS=${FORCE_STAGE1_CFLAGS:Q}
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

post-install:
	cd ${PREFIX}/info && for f in *.info; do \
		perl -pi -e 's/-VSS/-'${VSS:Q}/g $$f; \
		mv $$f $${f%.info}-${VSS}.info; \
	done
	mv ${PREFIX}/lib/fpic/libiberty.a \
	    ${PREFIX}/lib/gcc/${OStriplet}/${VSN}/fpic/
	rmdir ${PREFIX}/lib/fpic
	mv ${PREFIX}/lib/libiberty.a ${PREFIX}/lib/gcc/${OStriplet}/${VSN}/
	cd ${PREFIX}/lib/gcc/${OStriplet}/${VSN} && \
	    rm -f libgcc_s.so fpic/libgcc_s.so && \
	    for a in fpic/*.so.*; do \
		ln -f $$a .; \
	done && rm -f fpic/libgcc_s.so.*

.if make(whatif-depends)
USE_COMPILER:=		system
.endif

.include <bsd.port.mk>

_PASS_CC=		${_ORIG_CC}
AUTOCONF_ENV+=		MKSH=${MKSH:Q} PORTSDIR=${PORTSDIR:Q} WRKSRC=${WRKSRC:Q}
