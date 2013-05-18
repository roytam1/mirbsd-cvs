# $MirOS: ports/lang/python/python.port.mk,v 1.3 2007/07/19 20:34:48 bsiegert Exp $
# $OpenBSD: python.port.mk,v 1.10 2004/08/06 07:33:19 xsa Exp $

MODPY_VERSION?=		2.3
MODPY_MINPKG?=		2.3.5-1

_MODPY_BUILD_DEPENDS=	:python->=${MODPY_MINPKG}:lang/python/${MODPY_VERSION}

.if ${NO_BUILD:L} == "no"
BUILD_DEPENDS+=		${_MODPY_BUILD_DEPENDS}
.endif
RUN_DEPENDS+=		${_MODPY_BUILD_DEPENDS}

.if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MODPY_EXPAT_DEPENDS=	:python-expat-${MODPY_VERSION}*:lang/python/${MODPY_VERSION},-expat	
MODPY_TKINTER_DEPENDS=	:python-tkinter-${MODPY_VERSION}*:lang/python/${MODPY_VERSION},-tkinter
.endif

MODPY_BIN=		${LOCALBASE}/bin/python${MODPY_VERSION}
MODPY_INCDIR=		${LOCALBASE}/include/python${MODPY_VERSION}
MODPY_LIBDIR=		${LOCALBASE}/lib/python${MODPY_VERSION}
MODPY_SITEPKG=		${MODPY_LIBDIR}/site-packages

SUBST_VARS+=		MODPY_VERSION

MODPY_USE_DISTUTILS?=	Yes

.if ${MODPY_USE_DISTUTILS:L} == "yes"

# usually setup.py but Setup.py can be found too
MODPY_SETUP?=		setup.py

# build or build_ext are commonly used
MODPY_DISTUTILS_BUILD?=		build --build-base=${WRKSRC}
MODPY_DISTUTILS_INSTALL?=	install --prefix=${PREFIX}

_MODPY_CMD=	@cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} \
			${MODPY_BIN} ./${MODPY_SETUP}

# dirty way to do it with no modifications in bsd.port.mk
.  if !target(do-build)
do-build:
	${_MODPY_CMD} ${MODPY_DISTUTILS_BUILD} ${MODPY_DISTUTILS_BUILDARGS}
.  endif

# extra documentation or scripts should be installed via post-install
.  if !target(do-install)
do-install:
	${_MODPY_CMD} ${MODPY_DISTUTILS_BUILD} ${MODPY_DISTUTILS_BUILDARGS} \
		${MODPY_DISTUTILS_INSTALL} ${MODPY_DISTUTILS_INSTALLARGS}
.  endif

.endif
