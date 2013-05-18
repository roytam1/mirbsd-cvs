# $MirOS: ports/databases/db/Makefile,v 1.10 2006/09/14 00:07:48 tg Exp $

BROKEN=			ask tg@ to re-add SEPARATE_BUILD

COMMENT=		Berkeley DB, revision 4
COMMENT-doc=		Berkeley DB documentation, revision 4
COMMENT-tcl=		Berkeley DB Tcl library, revision 4
COMMENT-cxx=		Berkeley DB C++ library, revision 4
DESCR=			${PKGDIR}/DESCR

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

VERSION=		4.2.52.4
DASH_VER=		2
DISTNAME=		db-${VERSION:R}
PKGNAME=		db-${VERSION}-${DASH_VER}
PKGNAME-doc=		db-doc-${VERSION}-${DASH_VER}
PKGNAME-tcl=		db-tcl-${VERSION}-${DASH_VER}
PKGNAME-cxx=		db-cxx-${VERSION}-${DASH_VER}
CATEGORIES=		databases
HOMEPAGE=		http://www.sleepycat.com/
MASTER_SITES=		ftp://sleepycat1.inetu.net/releases/ \
			${HOMEPAGE}/update/snapshot/
MASTER_SITES0=		${HOMEPAGE}/update/${VERSION:R}/
DIST_SUBDIR=		db4

TCL_VERSION=		8.4

# License: BSD + SleepyCat's additions.
# Must purchase license to redistribute if not distributing the source.
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PATCHFILES=		patch.4.2.52.1:0 patch.4.2.52.2:0
PATCHFILES+=		patch.4.2.52.3:0 patch.4.2.52.4:0

MULTI_PACKAGES=		-doc

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOGEN=		${SHELL} -c 'cd dist && . ./s_config'
CONFIGURE_SCRIPT=	${WRKSRC}/dist/configure
CONFIGURE_ARGS+=	--enable-compat185 
CONFIGURE_ARGS+=	--enable-dump185
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--includedir=$$\{prefix}/include/db4
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}/dist
WRKBUILD=		${WRKDIR}/build

PSEUDO_FLAVORS=		no_tcl no_cxx
FLAVOR?=
SUBPACKAGE?=

.if ${FLAVOR:L:Mno_tcl}
CONFIGURE_ARGS+=	--disable-tcl
NO_REGRESS=		Yes
.else
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
MULTI_PACKAGES+=	-tcl
. if !defined(PACKAGING) || ${SUBPACKAGE} == "-tcl"
LIB_DEPENDS+=		tcl84.1.0::lang/tcl/${TCL_VERSION}
. endif
CFLAGS+=		-I${LOCALBASE}/include/tcl${TCL_VERSION}
CONFIGURE_ARGS+=	--enable-tcl 
CONFIGURE_ARGS+=	--with-tcl=${LOCALBASE}/lib/tcl${TCL_VERSION}
# Regression suite requires Tcl.
CONFIGURE_ARGS+=	--enable-test

do-regress:
	cd ${WRKDIST}/build_unix && \
	tclsh${TCL_VERSION} ${FILESDIR}/do-regress.tcl

.endif

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=	--disable-cxx
.else
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
MULTI_PACKAGES+=	-cxx
CONFIGURE_ARGS+=	--enable-cxx
USE_CXX=		Yes
.endif

.if defined(PACKAGING) && !empty(SUBPACKAGE) && ${SUBPACKAGE} != "-doc"
RUN_DEPENDS+=		::databases/db
.endif

.include <bsd.port.mk>
