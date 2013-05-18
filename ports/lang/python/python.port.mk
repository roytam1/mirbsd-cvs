# $MirOS: ports/lang/python/python.port.mk,v 1.9 2008/10/05 00:41:28 tg Exp $
# $OpenBSD: python.port.mk,v 1.10 2004/08/06 07:33:19 xsa Exp $

CATEGORIES+=		lang/python

MODPY_VERSION?=		2.5
.if ${MODPY_VERSION} == "2.3"
MODPY_MINPKG?=		2.3.5-1
.elif ${MODPY_VERSION} == "2.5"
MODPY_MINPKG?=		2.5.2-9
.else
MODPY_MINPKG?=		${MODPY_VERSION}
.endif
.ifndef MODPY_MAXPKG
MODPY_MAXPKG!=		print ${MODPY_VERSION:R}.$$((${MODPY_VERSION:E} + 1))
.MAKEFLAGS:=		${.MAKEFLAGS} MODPY_MAXPKG=${MODPY_MAXPKG:Q}
.endif

_MODPY_BUILD_DEPENDS=	:python->=${MODPY_MINPKG},<=${MODPY_MAXPKG}:lang/python/${MODPY_VERSION}

.if ${NO_BUILD:L} == "no"
BUILD_DEPENDS+=		${_MODPY_BUILD_DEPENDS}
.endif
RUN_DEPENDS+=		${_MODPY_BUILD_DEPENDS}

.if defined(MODPY_SETUPTOOLS) && ${MODPY_SETUPTOOLS:U} == YES
# The setuptools module provides a package locator (site.py) that is
# required at runtime for the pkg_resources stuff to work
MODPY_SETUPUTILS_DEPEND?=:py-setuptools-*:devel/py-setuptools
MODPY_RUN_DEPENDS+=	${MODPY_SETUPUTILS_DEPEND}
BUILD_DEPENDS+=		${MODPY_SETUPUTILS_DEPEND}
# The setuptools uses test target
REGRESS_TARGET?=	test
.endif

.if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
.  if ${MODPY_VERSION} != "2.5"
MODPY_EXPAT_DEPENDS=	:python-expat-${MODPY_VERSION}*:lang/python/${MODPY_VERSION},-expat	
MODPY_TKINTER_DEPENDS=	:python-tkinter-${MODPY_VERSION}*:lang/python/${MODPY_VERSION},-tkinter
.  endif
.endif

MODPY_BIN=		${LOCALBASE}/bin/python${MODPY_VERSION}
MODPY_INCDIR=		${LOCALBASE}/include/python${MODPY_VERSION}
MODPY_LIBDIR=		${LOCALBASE}/lib/python${MODPY_VERSION}
MODPY_SITEPKG=		${MODPY_LIBDIR}/site-packages

SUBST_VARS:=		MODPY_EGG_VERSION MODPY_VERSION ${SUBST_VARS}

#XXX What the F…?
LDFLAGS+=		-L${MODPY_LIBDIR:Q}/config

MODPY_USE_DISTUTILS?=	Yes

.if ${MODPY_USE_DISTUTILS:L} == "yes"

# usually setup.py but Setup.py can be found too
MODPY_SETUP?=		setup.py

# build or build_ext are commonly used
MODPY_DISTUTILS_BUILD?=		build --build-base=${WRKSRC}

.if defined(MODPY_SETUPTOOLS) && ${MODPY_SETUPTOOLS:U} == YES
MODPY_DISTUTILS_INSTALL?=	install --prefix=${LOCALBASE} \
				--root=${DESTDIR} \
				--single-version-externally-managed
.else
MODPY_DISTUTILS_INSTALL?=	install --prefix=${PREFIX}
.endif

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

# setuptools supports regress testing from setup.py using a standard target
.  if !target(do-regress) && \
      defined(MODPY_SETUPTOOLS) && ${MODPY_SETUPTOOLS:U} == YES
do-regress:
	${_MODPY_CMD} ${REGRESS_TARGET}
.  endif

.endif
