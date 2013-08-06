# $MirOS$
# $OpenBSD: Makefile,v 1.86 2013/07/04 16:34:05 dcoppa Exp $

VMEM_WARNING=		Yes

# avoid segfaults from binaries compiled and then used during the build
.if ${MACHINE_ARCH} == "arm"
CFLAGS+=		-O1 -fno-stack-protector
.endif

HOMEPAGE=		http://www.cmake.org/
CATEGORIES=		devel
COMMENT=		portable build system
DISTNAME=		cmake-2.8.11.2
MASTER_SITES=		${HOMEPAGE}files/v2.8/

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_CXX=		Yes
LIB_DEPENDS+=		archive::archivers/libarchive
LIB_DEPENDS+=		curl::net/curl

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS=		--prefix=${PREFIX} \
			--datadir=/share/cmake \
			--docdir=/share/doc/cmake \
			--parallel=${MAKE_JOBS} \
			--system-libs \
			--verbose
CONFIGURE_ENV+=		MAKE=${MAKE_PROGRAM}
PORTHOME=		${WRKDIR}
SEPARATE_BUILD=		Yes
REGRESS_TARGET=		test
EXTRA_XAKE_FLAGS+=	VERBOSE=1

post-extract:
	echo 'include(Platform/OpenBSD)' >${WRKSRC}/Modules/Platform/MirBSD.cmake

pre-configure:
	cp ${FILESDIR}/*.cmake ${WRKSRC}/Modules/
	${SUBST_CMD} ${WRKSRC}/Modules/CMakeDetermineJavaCompiler.cmake \
		${WRKSRC}/Modules/FindJNI.cmake \
		${WRKSRC}/Modules/FindJava.cmake \
		${WRKSRC}/Modules/FindLuaLibs.cmake \
		${WRKSRC}/Modules/FindMPEG.cmake \
		${WRKSRC}/Modules/FindMPEG2.cmake \
		${WRKSRC}/Modules/FindQt.cmake \
		${WRKSRC}/Modules/FindQt4.cmake \
		${WRKSRC}/Modules/FindSDL.cmake \
		${WRKSRC}/Modules/FindTCL.cmake

post-install:
	rm -f ${WRKINST}/${LOCALBASE}/share/cmake/Modules/*.{beforesubst,orig}
	rm ${WRKINST}/${LOCALBASE}/share/cmake/Modules/Compiler/*.orig
	rm ${WRKINST}/${LOCALBASE}/share/cmake/Modules/Platform/*.orig

.include <bsd.port.mk>

_CIPHERS+=		sha256

.if !defined(_SYSTRACE_CMD) || empty(_SYSTRACE_CMD)
.  error You will want systrace to be enabled.
.endif
