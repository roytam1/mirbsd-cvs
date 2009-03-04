# $MirOS: ports/lang/ewe/Makefile,v 1.1 2008/10/05 15:26:57 tg Exp $

NOT_FOR_PLATFORM=	Interix:*:*

COMMENT=		Lunix Ewe (embedded Java) Virtual Machine
COMMENT-common=		Lunix Ewe common files and documentation
COMMENT-gtk1=		Lunix Ewe with GTK+1 front-end (stand-alone)
COMMENT-gtk1ne=		Lunix Ewe with GTK+1 front-end (executable only)
COMMENT-gtk2=		Lunix Ewe with GTK+2 front-end (stand-alone)
COMMENT-gtk2ne=		Lunix Ewe with GTK+2 front-end (executable only)
CATEGORIES=		lang java
VERSION=		1.49mb4
DISTNAME=		ewe-${VERSION}
HOMEPAGE=		http://www.ewesoft.com/M2.htm
RESPONSIBLE=		Thorsten Glaser <tg@freewrt.org>

# GNU LGPL Version 2 or later, Version 2.1 or later,
# GNU GPL Version 2 or later with library exception clause,
# some freely redistributable, some unclear
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>
.if (${OStype} == "Darwin")
HAVE_GAS=		No
.else
HAVE_GAS=		Yes
.endif

MULTI_PACKAGES=		-common -gtk1ne -gtk2ne
.if ${HAVE_GAS:L} == "yes"
MULTI_PACKAGES+=	-gtk1 -gtk2	# requires GNU as
.endif
SUBPACKAGE?=

.for _i in ${MULTI_PACKAGES}
PKGNAME${_i}=		ewe${_i}-${VERSION}-${DASH_VER}
.endfor

# Properties for all subpackages
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/hosted/other/}
WRKDIST=		${WRKDIR}/ewe
USE_CXX=		Yes
DESCR=			${PKGDIR}/DESCR
SUBST_VARS+=		VERSION

# Dependencies
BUILD_DEPENDS+=		:mirmake->=20090304:devel/mirmake
LIB_DEPENDS+=		jpeg::graphics/jpeg

.if !defined(PACKAGING) || \
    (${SUBPACKAGE} == "-gtk1") || (${SUBPACKAGE} == "-gtk2") || \
    (${SUBPACKAGE} == "-gtk1ne") || (${SUBPACKAGE} == "-gtk2ne")
USE_X11=		Yes
.endif

.if !defined(PACKAGING) || \
    (${SUBPACKAGE} == "-gtk1") || (${SUBPACKAGE} == "-gtk1ne")
LIB_DEPENDS+=		gdk,gtk,gmodule,glib::x11/gtk+1
.endif

.if !defined(PACKAGING) || \
    (${SUBPACKAGE} == "-gtk2") || (${SUBPACKAGE} == "-gtk2ne")
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		gdk-x11-2.0.0.3,gdk_pixbuf-2.0.0.3,gtk-x11-2.0.0.3::x11/gtk+
.endif

.if defined(PACKAGING) && \
    ((${SUBPACKAGE} == "-gtk1ne") || (${SUBPACKAGE} == "-gtk2ne") || \
    (empty(SUBPACKAGE) && (${HAVE_GAS:L} != "yes")))
RUN_DEPENDS+=		:ewe-common-${VERSION}-${DASH_VER}:lang/ewe,-common
.endif

.if defined(PACKAGING) && empty(SUBPACKAGE) && (${HAVE_GAS:L} != "yes")
PLIST=			${PKGDIR}/PLIST.nogas
.endif

# Building
CONFIGURE_STYLE=	bmake
MAKE_FILE=		BSDmakefile
ALL_TARGET=		ewe
MAKE_ENV+=		NOMAN=Yes

.include <bsd.port.mk>
