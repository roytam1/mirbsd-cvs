# $MirOS: ports/infrastructure/mk/bsd.port.mk,v 1.290 2015/07/19 00:00:00 tg Exp $
# $OpenBSD: bsd.port.mk,v 1.677 2005/01/06 19:30:34 espie Exp $
# $FreeBSD: bsd.port.mk,v 1.264 1996/12/25 02:27:44 imp Exp $
# $NetBSD: bsd.port.mk,v 1.62 1998/04/09 12:47:02 hubertf Exp $
#-
# This is the MirPorts Framework master system Makefile. It provides
# an infrastructure to be used within the framework by every port.
#
# Each port has a maintainer, which is the email address(es) of the person(s)
# to contact if you have questions/suggestions about that specific port.
# To obtain that address, just type
#	mmake show=RESPONSIBLE
# in the specific port's directory.
#
# For the MirPorts Framework, the master contact address is the mailing list:
#	mmake show=_MIRPORTS_ADDRESS

# Any variable or target starting with an underscore (e.g., _DEPEND_ECHO)
# is internal to bsd.port.mk, not part of the user's API, and liable to
# change without notice.

.if ${.MAKEFLAGS:MFLAVOUR=*}
ERRORS+=		"Use 'env FLAVOUR=${FLAVOUR:Q} ${MAKE}' instead."
.endif
.if ${.MAKEFLAGS:MSUBPACKAGE=*}
ERRORS+=		"Use 'env SUBPACKAGE=${SUBPACKAGE:Q} ${MAKE}' instead."
.endif

# Default sequence for "all" is:  fetch checksum extract patch configure build
#
# Please read the comments in the targets section below, you
# should be able to use the pre-* or post-* targets (which
# are available for every stage except checksum) or provide
# an overriding do-* target to do pretty much anything you
# want.
#
# For historical reasons, the distpatch target is a subtarget of patch.
# If you provide a do-patch, you MUST call distpatch explicitly.
# The sequence of hooks actually run is:
#
# pre-patch 'real distpatch' post-distpatch 'real patch' post-patch

# User settings
TRUST_PACKAGES?=	No
BIN_PACKAGES?=		No
CLEANDEPENDS?=		Yes
BULK?=			No
RECURSIVE_FETCH_LIST?=	Yes
WRKOBJDIR?=
FAKEOBJDIR?=
BULK_TARGETS?=

# special purpose user settings
PATCH_CHECK_ONLY?=	No
REFETCH?=		false

# Global path locations.
DISTDIR?=		${PORTSDIR}/Distfiles
BULK_COOKIES_DIR?=	${PORTSDIR}/Bulk
TEMPLATES?=		${PORTSDIR}/infrastructure/templates
TMPDIR?=		/tmp
WWW_PREFIX?=		/var/www

PKGREPOSITORY?=		${PORTSDIR}/Packages
CDROM_PACKAGES?=	${PKGREPOSITORY}/CDROM
FTP_PACKAGES?=		${PKGREPOSITORY}/FTP

WRKOBJDIR_${PKGPATH}?=		${WRKOBJDIR}
FAKEOBJDIR_${PKGPATH}?=		${FAKEOBJDIR}
BULK_${PKGPATH}?=		${BULK}
BULK_TARGETS_${PKGPATH}?=	${BULK_TARGETS}
CLEANDEPENDS_${PKGPATH}?=	${CLEANDEPENDS}

# Commands and command settings.
PKG_DBDIR?=		${LOCALBASE}/db/pkg
PKG_TMPDIR?=		/var/tmp
PKG_CMDDIR?=		${LOCALBASE}/sbin
PKG_CMD_ADD?=		${PKG_CMDDIR}/pkg_add
PKG_CMD_CREATE?=	${PKG_CMDDIR}/pkg_create
PKG_CMD_DELETE?=	${PKG_CMDDIR}/pkg_delete -c
PKG_CMD_INFO?=		${PKG_CMDDIR}/pkg_info
PKG_CMD_PKG?=		${PKG_CMDDIR}/pkg
PKG_CMD_UPGRADE?=	${PKG_CMDDIR}/pkg_upgrade

.if ${MACHINE_ARCH} != ${ARCH}
PKG_ARCH?=		${MACHINE_ARCH},${ARCH}
.else
PKG_ARCH?=		${MACHINE_ARCH}
.endif

# remount those mount points ro before fake.
# XXX tends to panic the OS
PROTECT_MOUNT_POINTS?=

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.if !defined(PERMIT_PACKAGE_CDROM) || !defined(PERMIT_PACKAGE_FTP) || \
  !defined(PERMIT_DISTFILES_CDROM) || !defined(PERMIT_DISTFILES_FTP)
ERRORS+=		"The licencing info for ${FULLPKGNAME} is incomplete."
ERRORS+=		"Please notify the MirPorts maintainer:"
ERRORS+=		"    ${RESPONSIBLE}"
_BAD_LICENCING=		Yes
PERMIT_PACKAGE_CDROM=	No
PERMIT_DISTFILES_CDROM=	No
PERMIT_PACKAGE_FTP=	No
PERMIT_DISTFILES_FTP=	No
.endif

# CDROM should be FTP exportable!
.if ${PERMIT_PACKAGE_CDROM:L} == "yes" && ${PERMIT_PACKAGE_FTP:L} != "yes"
ERRORS+=		"Package is marked as permit CDROM but not FTP."
.endif
.if ${PERMIT_DISTFILES_CDROM:L} == "yes" && ${PERMIT_DISTFILES_FTP:L} != "yes"
ERRORS+=		"Distfiles are marked as permit CDROM but not FTP."
.endif


.if defined(show)
.MAIN: show
show:
.  for _s in ${show}
	@echo ${${_s}:Q}
.  endfor
.elif defined(dump)
.MAIN: show
show:
.  for _s in ${dump}
	@echo ${_s:Q:Q}=${${_s}:Q:Q}
.  endfor
.elif defined(clean)
.MAIN: clean
.elif defined(for-build-depends)
.MAIN: for-build-depends
.elif defined(for-all-depends)
.MAIN: for-all-depends
.elif defined(for-run-depends)
.MAIN: for-run-depends
.else
.MAIN: all
.endif

FAKE?=			Yes
_LIBLIST=		${WRKDIR}/.liblist-${ARCH}${_FLAVOUR_EXT2}
_BUILDLIBLIST=		${WRKDIR}/.buildliblist-${ARCH}${_FLAVOUR_EXT2}

# need to go through an extra var because clean is set in stone,
# on the cmdline.
_clean=			${clean}
.if ${_clean:L:Mpackage} || ${_clean:L:Mpackages}
CLEANDEPENDS=		No
.endif
.if empty(_clean) || ${_clean:L} == "depends"
_clean+=		work
.endif
.if ${CLEANDEPENDS_${PKGPATH}:L} == "yes"
_clean+=		depends
.endif
.if ${_clean:L:Mwork}
_clean+=		fake
.endif
.if ${_clean:L:Mforce}
_clean+=		-f
.endif
# check that clean is clean
_okay_words=		-f bulk depends dist fake flavours force install \
			package packages readme sub work
.for _w in ${_clean:L}
.  if !${_okay_words:M${_w}}
ERRORS+=		"Fatal: unknown clean command: ${_w}"
.  endif
.endfor

NOMANCOMPRESS?=		Yes
DEF_UMASK?=		022

.if exists(${.CURDIR}/Makefile.${ARCH})
.  include "${.CURDIR}/Makefile.${ARCH}"
.elif exists(${.CURDIR}/Makefile.${MACHINE_ARCH})
.  include "${.CURDIR}/Makefile.${MACHINE_ARCH}"
.endif

NO_DEPENDS?=		No
NO_BUILD?=		No
NO_REGRESS?=		No
DIST_SUBDIR?=

.if !empty(DIST_SUBDIR)
FULLDISTDIR?=		${DISTDIR}/${DIST_SUBDIR}
.else
FULLDISTDIR?=		${DISTDIR}
.endif

.if exists(${.CURDIR}/patches.${ARCH})
PATCHDIR?=		${.CURDIR}/patches.${ARCH}
.elif exists(${.CURDIR}/patches.${MACHINE_ARCH})
PATCHDIR?=		${.CURDIR}/patches.${MACHINE_ARCH}
.else
PATCHDIR?=		${.CURDIR}/patches
.endif

PATCH_LIST?=		patch-*

.if exists(${.CURDIR}/scripts.${ARCH})
SCRIPTDIR?=		${.CURDIR}/scripts.${ARCH}
.elif exists(${.CURDIR}/scripts.${MACHINE_ARCH})
SCRIPTDIR?=		${.CURDIR}/scripts.${MACHINE_ARCH}
.else
SCRIPTDIR?=		${.CURDIR}/scripts
.endif

.if exists(${.CURDIR}/files.${ARCH})
FILESDIR?=		${.CURDIR}/files.${ARCH}
.elif exists(${.CURDIR}/files.${MACHINE_ARCH})
FILESDIR?=		${.CURDIR}/files.${MACHINE_ARCH}
.else
FILESDIR?=		${.CURDIR}/files
.endif

.if exists(${.CURDIR}/pkg.${ARCH})
PKGDIR?=		${.CURDIR}/pkg.${ARCH}
.elif exists(${.CURDIR}/pkg.${MACHINE_ARCH})
PKGDIR?=		${.CURDIR}/pkg.${MACHINE_ARCH}
.elif exists(${.CURDIR}/pkg/DESCR)
PKGDIR?=		${.CURDIR}/pkg
.else
PKGDIR?=		${.CURDIR}
.endif

PREFIX?=		${LOCALBASE}
TRUEPREFIX?=		${PREFIX}
DESTDIRNAME?=		DESTDIR
DESTDIR?=		${WRKINST}
P5SITE=			libdata/perl5/site_perl

MAKE_FLAGS?=		CC=${_PASS_CC:T:Q}
.if !defined(FAKE_FLAGS)
FAKE_FLAGS=		${DESTDIRNAME}=${WRKINST:Q}
.endif

CONFIGURE_STYLE?=

.if ${USE_GMAKE:L} == "yes" || ${USE_SCHILY:L} != "no"
BUILD_DEPENDS+=		::devel/gmake
MAKE_PROGRAM=		${GMAKE}
MAKE_FLAGS+=		MAKE=$(MAKE_PROGRAM)
FAKE_FLAGS+=		MAKE=$(MAKE_PROGRAM)
.  if ${USE_SCHILY:L} != "no"
MAKE_ENV+=		MAKEPROG=${MAKE_PROGRAM:Q} CCOM=cc
.  endif
.else
MAKE_PROGRAM=		${MAKE}
.endif

.if ${CONFIGURE_STYLE:L:Mautomake} || ${CONFIGURE_STYLE:L:Mautoconf} \
    || ${CONFIGURE_STYLE:L:Mautoupdate} || ${CONFIGURE_STYLE:L:Mautogen}
.  if !${CONFIGURE_STYLE:L:Mgnu}
CONFIGURE_STYLE+=	gnu
.  endif
.endif

SUBPACKAGE?=
FLAVOUR?=
FLAVOURS?=
PSEUDO_FLAVOURS?=
FLAVOURS+=		${PSEUDO_FLAVOURS}

.if !empty(FLAVOURS:L:Mregress) && empty(FLAVOUR:L:Mregress)
NO_REGRESS=		Yes
.endif

.if ${USE_MOTIF:L} != "no"
USE_X11=		Yes
MODULES+=		motif
.endif

.if !empty(SUBPACKAGE)
.  for _i in ${SUBPACKAGE}
.    if !defined(MULTI_PACKAGES) || empty(MULTI_PACKAGES:M${_i})
ERRORS+=		"Subpackage ${SUBPACKAGE} does not exist."
.    endif
.  endfor
.endif

# Support architecture and flavour dependent packing lists
SED_PLIST?=

MCZ_FETCH?=		No
.for _i in - 0 1 2 3 4 5 6 7 8 9
.  if defined(SVN_DISTPATH${_i:N-}) && !empty(SVN_DISTPATH${_i:N-})
SVN_DISTDIR${_i:N-}?=	${SVN_DISTPATH${_i:N-}:T}
.    if !defined(SVN_DISTFILE${_i:N-}) || empty(SVN_DISTFILE${_i:N-}) 
SVN_DISTFILE${_i:N-}=	${SVN_DISTDIR${_i:N-}:T}
.    endif
SVN_DISTREV${_i:N-}?=	1
.    if ${MCZ_FETCH:L} != "no"
MASTER_SITES${_i:N-}?=	${_MASTER_SITE_MIRBSD}
.    endif
.  elif defined(CVS_DISTREPO${_i:N-}) && !empty(CVS_DISTREPO${_i:N-})
.    if ${MCZ_FETCH:L} != "no"
MASTER_SITES${_i:N-}?=	${_MASTER_SITE_MIRBSD}
.    endif
.  else
.    undef SVN_DISTPATH${_i:N-}
.    undef CVS_DISTREPO${_i:N-}
.  endif
.endfor

DASH_VER?=		0
.if defined(DIST_NAME) && defined(DIST_DATE)
PKGNAME?=		${DIST_NAME}-${DIST_DATE}-${DASH_VER}
WRKDIST?=		${WRKDIR}/${DIST_NAME}
.elif defined(CVS_DISTREPO)
PKGNAME?=		${_CVS_DISTF:R}-${DASH_VER}
WRKDIST?=		${WRKDIR}/${CVS_DISTMODS}
.elif defined(SVN_DISTPATH)
PKGNAME?=		${SVN_DISTFILE}-${SVN_DISTREV}-${DASH_VER}
WRKDIST?=		${WRKDIR}/${SVN_DISTDIR}
.else
PKGNAME?=		${DISTNAME}-${DASH_VER}
WRKDIST?=		${WRKDIR}/${DISTNAME}
.endif
FULLPKGNAME?=		${PKGNAME}${FLAVOUR_EXT}
PKGFILE=		${PKGREPOSITORY}/${FULLPKGNAME}${PKG_SUFX}
_MASTER?=

.if defined(MULTI_PACKAGES) && !empty(MULTI_PACKAGES)
.  for _s in ${MULTI_PACKAGES}
.    if !defined(FULLPKGNAME${_s})
.      if defined(PKGNAME${_s})
FULLPKGNAME${_s} =	${PKGNAME${_s}}${FLAVOUR_EXT}
.      else
FULLPKGNAME${_s} =	${PKGNAME}${_s}${FLAVOUR_EXT}
.      endif
.    endif
PKGFILE${_s} =		${PKGREPOSITORY}/${FULLPKGNAME${_s}}${PKG_SUFX}
.  endfor
.endif

_SYSTRACE_COOKIE=	${WRKDIR}/systrace.policy
_WRKDIR_COOKIE=		${WRKDIR}/.extract_started
_EXTRACT_COOKIE=	${WRKDIR}/.extract_done
_PATCH_COOKIE=		${WRKDIR}/.patch_done
_DISTPATCH_COOKIE=	${WRKDIR}/.distpatch_done
_PREPATCH_COOKIE=	${WRKDIR}/.prepatch_done
_INSTALL_COOKIE=	${PKG_DBDIR}/${FULLPKGNAME${SUBPACKAGE}}/+CONTENTS
_BULK_COOKIE=		${BULK_COOKIES_DIR}/${FULLPKGNAME}
.if ${FAKE:L} == "yes"
_FAKE_COOKIE=		${WRKINST}/.fake_done
_INSTALL_PRE_COOKIE=	${WRKINST}/.install_started
.else
_INSTALL_PRE_COOKIE=	${WRKBUILD}/.install_started
_FAKE_COOKIE=		${WRKBUILD}/.fake_done
.endif
_PACKAGE_COOKIE=	${PKGFILE}
_CONFIGURE_COOKIE=	${WRKBUILD}/.configure_done
_BUILD_COOKIE=		${WRKBUILD}/.build_done
_REGRESS_COOKIE=	${WRKBUILD}/.regress_done

_ALL_COOKIES=		${_EXTRACT_COOKIE} ${_PATCH_COOKIE} \
			${_CONFIGURE_COOKIE} ${_INSTALL_PRE_COOKIE} \
			${_BUILD_COOKIE} ${_REGRESS_COOKIE} \
			${_PACKAGE_COOKIES} ${_DISTPATCH_COOKIE} \
			${_PREPATCH_COOKIE} ${_FAKE_COOKIE} \
			${_WRKDIR_COOKIE} ${_DEPlib_COOKIES} \
			${_DEPbuild_COOKIES} ${_DEPrun_COOKIES} \
			${_DEPregress_COOKIES}

_MAKE_COOKIE?=		touch -f

# Miscellaneous overridable commands:
GMAKE?=			gmake
USE_CCACHE?=		No

CHECKSUM_FILE?=		${.CURDIR}/distinfo

# Don't touch!!! Used for generating checksums.
_CIPHERS=		rmd160 tiger sha1 sha256 md5

_PORTPATH?=		${LOCALBASE}/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:${LOCALBASE}/sbin
.if ${USE_X11:L} == "yes"
_PORTPATH:=		${_PORTPATH}:${X11BASE}/bin
.endif
PORTPATH?=		${WRKDIR}/bin:${_PORTPATH}

# Add any COPTS to CFLAGS.
CPPFLAGS+=		-idirafter ${LOCALBASE}/include
.if ${USE_X11:L} == "yes"
CPPFLAGS+=		-idirafter ${X11BASE}/include
.endif
CFLAGS+=		${COPTS} ${CPPFLAGS}
CXXFLAGS+=		${CXXOPTS} ${CPPFLAGS}
.if defined(WARNINGS) && ${WARNINGS:L} == "yes"
.  if defined(CDIAGFLAGS)
CFLAGS+=		${CDIAGFLAGS}
.  endif
.  if defined(CXXDIAGFLAGS)
CXXFLAGS+=		${CXXDIAGFLAGS}
.  endif
.endif
# cf. http://libtorrent.rakshasa.no/wiki/LibTorrentKnownIssues#Badcodeproducedwith-fomit-frame-pointer
CXXFLAGS+=		-fno-omit-frame-pointer
LDFLAGS+=		${LDSTATIC} -Wl,--library-after=${LOCALBASE}/lib
.if ${OBJECT_FMT} == "ELF"
LDFLAGS+=		-Wl,-rpath -Wl,${LOCALBASE}/lib
.endif

_DEFCOPTS_pcc?=		-O

NO_CXX?=		No	# inhibit use of C++ ports
USE_COMPILER?=		system
.if ${USE_COMPILER:L} == "gcc4.4"
HAS_CXX:=		port
_CXX_LIB_DEPENDS=	# empty as the libs are not in LOCALBASE/lib/ directly
.endif
.if ${USE_CXX:L} == "yes"
.  if ${NO_CXX:L} == "yes"
NO_CXX=			C++ is explicitly disabled
.  elif ${HAS_CXX:L} == "base"
CXX?=			g++
NO_CXX=			No
.  elif ${HAS_CXX:L} == "port"
LIB_DEPENDS+=		${_CXX_LIB_DEPENDS}
NO_CXX=			No
.  elif ${HAS_CXX:L} != "reason"
NO_CXX=			C++ is not supported on this system
.  endif
.else
NO_CXX=			not explicitly requested by this port
.endif
_ORIG_CC:=		${CC}
_ORIG_CXX:=		${CXX}
.if ${USE_COMPILER:L} == "pcc"
BUILD_DEPENDS+=		:pcc-*:lang/pcc
USE_CCACHE:=		No
_DEFCOPTS:=		${_DEFCOPTS_pcc}
_DEFcTOsOPTS:=		-S
_ORIG_CC:=		pcc
_ORIG_CXX:=		false
.elif ${USE_COMPILER:L} == "gcc4.4"
BUILD_DEPENDS+=		:gcc-4.4.7-*:lang/egcs/gcc4.4
RUN_DEPENDS+=		:gcc-rtl-4.4.7-*:lang/egcs/gcc4.4,-rtl
_ORIG_CC:=		gcc-4.4
_ORIG_CXX:=		g++-4.4
.elif ${USE_COMPILER:L} != "system"
.  error invalid compiler: ${USE_COMPILER}
.endif
_USE_CC:=		${_ORIG_CC}
_USE_CXX:=		${_ORIG_CXX}
.if ${NO_CXX:L} != "no"
_USE_CXX:=		false
.endif
_USE_CCSTD?=		-std=gnu99
_USE_CXXSTD?=		# the equivalent?

.if ${USE_CCACHE:L} == "yes"
CCACHE_DEPENDS?=	:ccache->=2.4-3:devel/ccache
BUILD_DEPENDS+=		${CCACHE_DEPENDS}
CCACHE_DIR?=		${HOME}/.etc/ccache
.  if !empty(CCACHE_DEPENDS)
_USE_CC:=		env CCACHE_DIR=${CCACHE_DIR:Q} CCACHE_NOLINK=1 \
			    CCACHE_UMASK=002 ccache ${_USE_CC}
.    if ${NO_CXX:L} == "no"
_USE_CXX:=		env CCACHE_DIR=${CCACHE_DIR:Q} CCACHE_NOLINK=1 \
			    CCACHE_UMASK=002 ccache ${_USE_CXX}
.    endif
.  endif
.endif

.if !empty(WRKOBJDIR_${PKGPATH})
WRKDIR?=		${WRKOBJDIR_${PKGPATH}}/${PKGNAME}${_FLAVOUR_EXT2}
.else
WRKDIR?=		${.CURDIR}/w-${PKGNAME}${_FLAVOUR_EXT2}
.endif

.undef CC
.undef CXX
#.if _ORIG_CC is a gcc (and _ORIG_CXX is a g++)
_MPWRAP_CC=		mpgcc
_MPWRAP_CXX=		mpg++
#.else
#_MPWRAP_CC=		mpcc
#_MPWRAP_CXX=		mpcxx
#.endif
_PASS_CC=		${WRKDIR}/bin/${_MPWRAP_CC}
_PASS_CXX=		${WRKDIR}/bin/${_MPWRAP_CXX}
.if ${USE_COMPILER:L} == "pcc"
_PASS_CC=		${_ORIG_CC}
_PASS_CXX=		${_ORIG_CXX}
.endif
CC=			${_PASS_CC:T}
CXX=			${_PASS_CXX:T}

MAKE_FILE?=		Makefile
PORTHOME?=		/${PKGNAME}_writes_to_HOME

MAKE_ENV+=		HOME=${PORTHOME:Q} PATH=${PORTPATH:Q} \
			PREFIX=${PREFIX:Q} TRUEPREFIX=${PREFIX:Q} \
			LOCALBASE=${LOCALBASE:Q} X11BASE=${X11BASE:Q} \
			CC=${_PASS_CC:T:Q} LDFLAGS=${LDFLAGS:Q} ${DESTDIRNAME}= \
			CXX=${_PASS_CXX:T:Q} CFLAGS=${CFLAGS:M*:Q} \
			BINOWN=${BINOWN:Q} BINGRP=${BINGRP:Q} \
			EXTRA_SYS_MK_INCLUDES=\"${PORTSDIR:Q}/infrastructure/mk/mirports.bsd.mk\"
.if ${NO_CXX:L} == "no"
MAKE_ENV+=		CXXFLAGS=${CXXFLAGS:M*:Q}
.endif

.if defined(LDADD) && !empty(LDADD)
MAKE_ENV+=		LDADD=${LDADD:Q}
.endif

DISTORIG?=		.bak.orig
PATCH?=			/usr/bin/patch
PATCHORIG?=		.orig
PATCH_STRIP?=		-p0
PATCH_DIST_STRIP?=	-p0

PATCH_DEBUG?=		No
.if ${PATCH_DEBUG:L} != "no"
PATCH_ARGS?=		-b -d ${WRKDIST} -z ${PATCHORIG} -E ${PATCH_STRIP}
PATCH_DIST_ARGS?=	-b -z ${DISTORIG} -d ${WRKDIST} -E ${PATCH_DIST_STRIP}
.else
PATCH_ARGS?=		-b -d ${WRKDIST} -z ${PATCHORIG} --forward --quiet -E ${PATCH_STRIP}
PATCH_DIST_ARGS?=	-b -z ${DISTORIG} -d ${WRKDIST} --forward --quiet -E ${PATCH_DIST_STRIP}
.endif

.if ${PATCH_CHECK_ONLY:L} == "yes"
PATCH_ARGS+=		-C
PATCH_DIST_ARGS+=	-C
.endif

NO_SYSTRACE?=		No
.if ${NO_SYSTRACE:L} == "no"
_SYSTRACE_CMD?=		/bin/systrace ${_SYSTRACE_ARGS} -f ${_SYSTRACE_COOKIE}
.else
_SYSTRACE_CMD=
.endif

TAR?=			/bin/tar
UNZIP?=			unzip
BZIP2?=			bzip2
AWK?=			/usr/bin/awk
M4?=			/usr/bin/m4

.if !empty(FAKEOBJDIR_${PKGPATH})
WRKINST?=		${FAKEOBJDIR_${PKGPATH}}/${PKGNAME}${_FLAVOUR_EXT2}
.else
WRKINST?=		${WRKDIR}/fake-${ARCH}${_FLAVOUR_EXT2}
.endif

WRKSRC?=		${WRKDIST}
WRKBUILD?=		${WRKSRC}
WRKPKG?=		${WRKBUILD}/.pkg
WRKCONF?=		${WRKBUILD}

ALL_TARGET?=		all
INSTALL_TARGET?=	install
FAKE_TARGET?=		${INSTALL_TARGET}

.for _i in perl gnu imake
.  if ${CONFIGURE_STYLE:L:M${_i}}
MODULES+=		${_i}
.  endif
.endfor

.if defined(MODULES)
_MODULES_DONE=
.  include "${PORTSDIR}/infrastructure/mk/modules.port.mk"
.endif

EXTRA_XAKE_FLAGS+=	SHELL=${SHELL:Q}
MAKE_FLAGS+=		${EXTRA_MAKE_FLAGS} ${EXTRA_XAKE_FLAGS}
FAKE_FLAGS+=		${EXTRA_FAKE_FLAGS} ${EXTRA_XAKE_FLAGS}

# Build FLAVOUR_EXT, checking that no flavours are misspelled
FLAVOUR_EXT:=
# _FLAVOUR_EXT2 is used internally for working directories.
# It encodes flavours and pseudo-flavours.
_FLAVOUR_EXT2:=

# Create the basic sed substitution pipeline for fragments
# (applies only to PLIST for now)
.if !empty(FLAVOURS)
.  for _i in ${FLAVOURS:L}
.    if empty(FLAVOUR:L:M${_i})
SED_PLIST+=	|sed \
		-e '/^!%%${_i}%%$$/r${PKGDIR}/PFRAG.no-${_i}${SUBPACKAGE}' \
		-e '//d' \
		-e '/^%%${_i}%%$$/d'
.    else
_FLAVOUR_EXT2:=	${_FLAVOUR_EXT2}-${_i}
.    if empty(PSEUDO_FLAVOURS:L:M${_i})
FLAVOUR_EXT:=	${FLAVOUR_EXT}-${_i}
.    endif
SED_PLIST+=	|sed \
		-e '/^!%%${_i}%%$$/d' \
		-e '/^%%${_i}%%$$/r${PKGDIR}/PFRAG.${_i}${SUBPACKAGE}' \
		-e '//d'
.    endif
.  endfor
.endif

.if !empty(FLAVOURS:M[0-9]*)
ERRORS+=		"Flavour cannot start with a digit."
.endif

.if !empty(FLAVOUR)
.  if !empty(FLAVOURS)
.    for _i in ${FLAVOUR:L}
.      if empty(FLAVOURS:L:M${_i})
ERRORS+=		"Unknown flavour: ${_i}"
ERRORS+=		"Possible flavours are: ${FLAVOURS}"
.      endif
.    endfor
.  else
ERRORS+=		"No flavours for this port."
.  endif
.endif

###
### Variable setup that can happen after modules
###

REGRESS_TARGET?=	regress
REGRESS_FLAGS?=		${MAKE_FLAGS}

.if ${FAKE:L} == "yes"
_PACKAGE_COOKIE_DEPS=	${_FAKE_COOKIE}
.else
_PACKAGE_COOKIE_DEPS=	${_INSTALL_COOKIE}
.endif

_PACKAGE_COOKIES=	${_PACKAGE_COOKIE}
.if ${BIN_PACKAGES:L} == "yes"
${_PACKAGE_COOKIE}:
	@cd ${.CURDIR} && exec ${MAKE} ${_PACKAGE_COOKIE_DEPS}
.else
${_PACKAGE_COOKIE}: ${_PACKAGE_COOKIE_DEPS}
.endif
	@cd ${.CURDIR} && SUBPACKAGE= FLAVOUR=${FLAVOUR:Q} PACKAGING= exec ${MAKE} _package
.if !defined(PACKAGE_NOINSTALL)
	@${_MAKE_COOKIE} $@
.endif

.for _s in ${MULTI_PACKAGES}
_PACKAGE_COOKIE${_s} =	${PKGFILE${_s}}
_PACKAGE_COOKIES+=	${_PACKAGE_COOKIE${_s}}
.endfor

.if empty(SUBPACKAGE)
.  if empty(FLAVOUR_EXT)
FULLPKGPATH=		${PKGPATH},
.  else
FULLPKGPATH=		${PKGPATH}${FLAVOUR_EXT:S/-/,/g}
.  endif
.else
FULLPKGPATH=		${PKGPATH},${SUBPACKAGE}${FLAVOUR_EXT:S/-/,/g}
.endif

# A few aliases for *-install targets
INSTALL_PROGRAM?=	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} \
			    -o ${BINOWN} -g ${BINGRP} -m ${BINMODE}
INSTALL_LIB?=		${INSTALL} ${INSTALL_COPY} \
			    -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE}
INSTALL_SCRIPT?=	${INSTALL} ${INSTALL_COPY} \
			    -o ${BINOWN} -g ${BINGRP} -m ${BINMODE}
INSTALL_DATA?=		${INSTALL} ${INSTALL_COPY} \
			    -o ${SHAREOWN} -g ${SHAREGRP} -m ${SHAREMODE}
INSTALL_MAN?=		${INSTALL} ${INSTALL_COPY} \
			    -o ${MANOWN} -g ${MANGRP} -m ${MANMODE}

INSTALL_PROGRAM_DIR?=	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE}
INSTALL_LIB_DIR?=	${INSTALL_PROGRAM_DIR}
INSTALL_SCRIPT_DIR?=	${INSTALL_PROGRAM_DIR}
INSTALL_DATA_DIR?=	${INSTALL} -d -o ${SHAREOWN} -g ${SHAREGRP} -m ${DIRMODE}
INSTALL_MAN_DIR?=	${INSTALL} -d -o ${MANOWN} -g ${MANGRP} -m ${DIRMODE}

_INSTALL_MACROS=	BSD_INSTALL_PROGRAM=${INSTALL_PROGRAM:Q} \
			BSD_INSTALL_LIB=${INSTALL_LIB:Q} \
			BSD_INSTALL_SCRIPT=${INSTALL_SCRIPT:Q} \
			BSD_INSTALL_DATA=${INSTALL_DATA:Q} \
			BSD_INSTALL_MAN=${INSTALL_MAN:Q} \
			BSD_INSTALL_PROGRAM_DIR=${INSTALL_PROGRAM_DIR:Q} \
			BSD_INSTALL_LIB_DIR=${INSTALL_LIB_DIR:Q} \
			BSD_INSTALL_SCRIPT_DIR=${INSTALL_SCRIPT_DIR:Q} \
			BSD_INSTALL_DATA_DIR=${INSTALL_DATA_DIR:Q} \
			BSD_INSTALL_MAN_DIR=${INSTALL_MAN_DIR:Q}
MAKE_ENV+=		${_INSTALL_MACROS}
SCRIPTS_ENV+=		${_INSTALL_MACROS}

# setup systrace variables
SYSTRACE_FILTER?=	${PORTSDIR}/infrastructure/templates/systrace.filter
_SYSTRACE_POLICIES+=	${SHELL} /usr/bin/env \
			${_MIRMAKE_EXE} ${LOCALBASE}/bin/gmake
SYSTRACE_SUBST_VARS+=	DISTDIR PKG_TMPDIR PORTSDIR TMPDIR WRKDIR
.for _v in ${SYSTRACE_SUBST_VARS}
_SYSTRACE_SED_SUBST+=	-e 's,$${${_v}},${${_v}},g'
.endfor

# Create the generic variable substitution list, from subst vars
SUBST_VARS+=		MACHINE_ARCH ARCH HOMEPAGE PREFIX SYSCONFDIR \
			FLAVOUR_EXT RESPONSIBLE VSN
.if ${USE_X11:L} == "yes"
SUBST_VARS+=		X11BASE
.endif
_SED_SUBST=		sed
.for _v in ${SUBST_VARS}
_SED_SUBST+=		-e 's|$${${_v}}|${${_v}}|g'
.endfor
_SED_SUBST+=		-e 's,$${FLAVOURS},${FLAVOUR_EXT},g' -e 's,$$\\,$$,g'
# and append it to the PLIST substitution pipeline
SED_PLIST+=		|${_SED_SUBST}

SUBST_CMD=		perl -pi
.for i in ${SUBST_VARS}
SUBST_CMD+=		-e "s%\\\$${$i}%${$i}%;"
.endfor

.if !defined(NO_LIBTOOLISE_PLIST) || (${NO_LIBTOOLISE_PLIST:L} == "no")
SED_PLIST+=		| (cd ${WRKINST}${PREFIX}; LOCALBASE=${LOCALBASE} perl -W ${PORTSDIR}/infrastructure/scripts/unlibtoolise || rm -f $@.tmp)
.endif

# find out the most appropriate PLIST source
.if !defined(PLIST) \
    && exists(${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.${ARCH})
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.${ARCH}
.elif !defined(PLIST) \
    && exists(${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.${MACHINE_ARCH})
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.${MACHINE_ARCH}
.endif
.if !defined(PLIST) && ${NO_SHARED_LIBS:L} == "yes" \
    && exists(${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.noshared)
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}.noshared
.endif
.if !defined(PLIST) && exists(${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT})
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}${FLAVOUR_EXT}
.endif
.if !defined(PLIST) && exists(${PKGDIR}/PLIST${SUBPACKAGE}.${ARCH})
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}.${ARCH}
.elif !defined(PLIST) && exists(${PKGDIR}/PLIST${SUBPACKAGE}.${MACHINE_ARCH})
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}.${MACHINE_ARCH}
.endif
.if !defined(PLIST) && ${NO_SHARED_LIBS:L} == "yes" \
    && exists(${PKGDIR}/PLIST${SUBPACKAGE}.noshared)
PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}.noshared
.endif
PLIST?=			${PKGDIR}/PLIST${SUBPACKAGE}

# Likewise for DESCR/MESSAGE/COMMENT
.if defined(COMMENT${SUBPACKAGE}${FLAVOUR_EXT})
_COMMENT=		${COMMENT${SUBPACKAGE}${FLAVOUR_EXT}}
.elif defined(COMMENT${SUBPACKAGE})
_COMMENT=		${COMMENT${SUBPACKAGE}}
.endif

.if exists(${PKGDIR}/MESSAGE${SUBPACKAGE})
MESSAGE?=		${PKGDIR}/MESSAGE${SUBPACKAGE}
.endif

DESCR?=			${PKGDIR}/DESCR${SUBPACKAGE}

MTREE_FILE?=
.if ${PREFIX} == "/usr"
MTREE_FILE+=		${PORTSDIR}/infrastructure/templates/4.4BSD.dist
.endif
MTREE_FILE+=		${LOCALBASE}/db/fake.mtree

# Fill out package command, and package dependencies
_PKG_PREREQ=		${WRKPKG}/PLIST${SUBPACKAGE} \
			${WRKPKG}/DESCR${SUBPACKAGE} \
			${WRKPKG}/COMMENT${SUBPACKAGE}
# Note that if you override PKG_ARGS, you will not get correct dependencies;
# you can add stuff to PKG_ARGS_ADD instead
.if !defined(PKG_ARGS)
PKG_ARGS=		-v -c ${WRKPKG:Q}/COMMENT${SUBPACKAGE:Q} \
			-d ${WRKPKG}/DESCR${SUBPACKAGE}
PKG_ARGS+=		-f ${WRKPKG}/PLIST${SUBPACKAGE} -p ${PREFIX}
.  if exists(${PKGDIR}/INSTALL${SUBPACKAGE})
PKG_ARGS+=		-i ${WRKPKG}/INSTALL${SUBPACKAGE}
_PKG_PREREQ+=		${WRKPKG}/INSTALL${SUBPACKAGE}
.  endif
.  if exists(${PKGDIR}/DEINSTALL${SUBPACKAGE})
PKG_ARGS+=		-k ${WRKPKG}/DEINSTALL${SUBPACKAGE}
_PKG_PREREQ+=		${WRKPKG}/DEINSTALL${SUBPACKAGE}
.  endif
.  if exists(${PKGDIR}/REQ${SUBPACKAGE})
PKG_ARGS+=		-r ${WRKPKG}/REQ${SUBPACKAGE}
_PKG_PREREQ+=		${WRKPKG}/REQ${SUBPACKAGE}
.  endif
.  if defined(MESSAGE) && ${MESSAGE} != "/dev/null"
PKG_ARGS+=		-D ${WRKPKG}/MESSAGE${SUBPACKAGE}
_PKG_PREREQ+=		${WRKPKG}/MESSAGE${SUBPACKAGE}
.  endif
.endif
.if defined(EMUL) && !empty(EMUL)
PKG_ARGS+=		-e ${EMUL:Q}
.endif
.if ${FAKE:L} == "yes"
PKG_ARGS+=		-S ${WRKINST}
.endif
PKG_ARGS+=		${PKG_ARGS_ADD}
.if !defined(_COMMENT)
ERRORS+=		"Missing port comment in Makefile."
.endif
.if ${FULLPKGNAME:C/-[0-9][0-9]*(-[a-zA-Z][^-]*)*$//:C/^.*-([^-]*)$/\1/:C/^[0-9][0-9._a-zA-Z]*$//}
ERRORS+=		"Invalid version number in main package '${FULLPKGNAME}': ${FULLPKGNAME:C/-[0-9][0-9]*(-[a-zA-Z][^-]*)*$//:C/^.*-([^-]*)$/\1/:C/^[0-9][0-9._a-zA-Z]*$//}."
.endif
.if defined(MULTI_PACKAGES) && !empty(MULTI_PACKAGES)
.  for _s in ${MULTI_PACKAGES}
.    if ${FULLPKGNAME${_s}:C/-[0-9][0-9]*(-[a-zA-Z][^-]*)*$//:C/^.*-([^-]*)$/\1/:C/^[0-9][0-9._a-zA-Z]*$//}
ERRORS+=		"Invalid version number in '${_s}' subpackage '${FULLPKGNAME${_s}}': ${FULLPKGNAME${_s}:C/-[0-9][0-9]*(-[a-zA-Z][^-]*)*$//:C/^.*-([^-]*)$/\1/:C/^[0-9][0-9._a-zA-Z]*$//}."
.    endif
.  endfor
.endif

CHMOD?=			/bin/chmod
CHOWN?=			/sbin/chown
GUNZIP_CMD?=		/usr/bin/gunzip -f
GZCAT?=			/usr/bin/gzip -dc
GZIP?=			-n9
GZIP_CMD?=		/usr/bin/gzip -nf ${GZIP}
LDCONFIG?=		[ ! -x /sbin/ldconfig ] || /sbin/ldconfig
STRIP?=			/usr/bin/strip

# Autoconf scripts MAY tend to use bison by default otherwise
YACC?=			yacc
# XXX ${SETENV} is needed in front of var=value lists whenever the next
# command is expanded from a variable, as this could be a shell construct
SETENV?=		/usr/bin/env -i
# Override only if port depends e.g. on GNU bash features. Not recommended.
SH?=			${SHELL}

# Used to print all the '===>' style prompts - override this to turn them off.
ECHO_MSG?=		echo

.for _i _j in _OUR_LDLIBPATH LD_LIBRARY_PATH PERL5LIB PERL5LIB
.  if defined(${_i}) && !empty(${_i})
SETENV+=		${_j}=${${_i}:Q}
.  endif
.endfor

.for _i in ${SETENV_TO_KEEP}
.  if defined(${_i}) && !empty(${_i})
SETENV+=		${_i:Q}=${${_i}:Q}
.  endif
.endfor

# basic master sites configuration

.if exists(${PORTSDIR}/infrastructure/db/network.conf)
.  include "${PORTSDIR}/infrastructure/db/network.conf"
.else
.  include "${PORTSDIR}/infrastructure/templates/network.conf.template"
.endif
# Where to put distfiles that don't have any other master site
#
MASTER_SITE_LOCAL?= \
	ftp://ftp.netbsd.org/pub/NetBSD/packages/distfiles/LOCAL_PORTS/ \
	ftp://ftp.freebsd.org/pub/FreeBSD/distfiles/LOCAL_PORTS/

# Empty declarations to avoid "variable XXX is recursive" errors
MASTER_SITES?=
# I guess we're in the master distribution business! :)  As we gain mirror
# sites for distfiles, add them to this list.
.if !defined(MASTER_SITE_OVERRIDE)
MASTER_SITES:=	${MASTER_SITES} ${MASTER_SITE_BACKUP}
.else
MASTER_SITES:=	${MASTER_SITE_OVERRIDE} ${MASTER_SITES}
.endif

# _SITE_SELECTOR chooses the value of sites based on select.
_SITE_SELECTOR=	case $$select in

.for _I in 0 1 2 3 4 5 6 7 8 9
.  if defined(MASTER_SITES${_I})
.    if !defined(MASTER_SITE_OVERRIDE)
MASTER_SITES${_I}:=	${MASTER_SITES${_I}} ${MASTER_SITE_BACKUP}
.    else
MASTER_SITES${_I}:=	${MASTER_SITE_OVERRIDE} ${MASTER_SITES${_I}}
.    endif
_SITE_SELECTOR+=	*:${_I}) sites=${MASTER_SITES${_I}:Q};;
.  else
_SITE_SELECTOR+=	*:${_I}) echo >&2 \
			    "Error: MASTER_SITES${_I} not defined";;
.  endif
.endfor
_SITE_SELECTOR+=	*) sites=${MASTER_SITES:Q};; esac


# Code to handle ports distfiles on a CDROM.  The distfiles
# are located in /cdrom/distfiles/${DIST_SUBDIR}/ (assuming that the
# CD-ROM is mounted on /cdrom).
.if exists(/cdrom/distfiles)
CDROM_SITE?=		/cdrom/distfiles/${DIST_SUBDIR}
.else
CDROM_SITE?=
.endif

FETCH_SYMLINK_DISTFILES?=Yes
.if !empty(CDROM_SITE)
.  if ${FETCH_SYMLINK_DISTFILES:L} == "yes"
_CDROM_OVERRIDE=	if test -e ${CDROM_SITE}/$$f && \
			    ln -s ${CDROM_SITE}/$$f .; then exit 0; fi
.  else
_CDROM_OVERRIDE=	if cp -f ${CDROM_SITE}/$$f .; then exit 0; fi
.  endif
.else
_CDROM_OVERRIDE=	:
.endif

_CVS_FDEP=
.for _i in - 0 1 2 3 4 5 6 7 8 9
.  undef _CVS_DISTF${_i:N-}
.  if defined(CVS_DISTREPO${_i:N-})
CVS_DISTFILE${_i:N-}?=	${CVS_DISTMODS${_i:N-}}
_CVS_DISTF${_i:N-}=	${CVS_DISTFILE${_i:N-}}-
.    if defined(CVS_DISTTAGS${_i:N-})
.      for _j in ${CVS_DISTTAGS${_i:N-}:C![^0-9a-zA-Z_-]!!g}
_CVS_DISTF${_i:N-}:=	${_CVS_DISTF${_i:N-}}T${_j}-
.      endfor
.    endif
.    if defined(CVS_DISTDATE${_i:N-})
.      for _j in ${CVS_DISTDATE${_i:N-}:C![^0-9]!!g}
_CVS_DISTF${_i:N-}:=	${_CVS_DISTF${_i:N-}}${_j}
.      endfor
.    endif
.    if defined(CVS_DISTTAGS${_i:N-}) || defined(CVS_DISTDATE${_i:N-})
_CVS_DISTF${_i:N-}:=	${_CVS_DISTF${_i:N-}:S/-$//}.mcz
.    else
ERRORS+=		"neither CVS_DISTDATE${_i:N-} nor CVS_DISTTAGS${_i:N-} defined"
.    endif
_CVS_FETCH${_i:N-}=	${MKSH} ${PORTSDIR}/infrastructure/scripts/mkmcz \
			    ${_MKMCZ_OPTS} \
			    ${FULLDISTDIR:Q}/${_CVS_DISTF${_i:N-}:Q} \
			    '${CVS_DISTREPO${_i:N-}}' \
			    '${CVS_DISTDATE${_i:N-}}' \
			    '${CVS_DISTTAGS${_i:N-}}' \
			    ${CVS_DISTMODS${_i:N-}:Q}
_CVS_FDEP+=		mpczar
.  elif defined(SVN_DISTPATH${_i:N-})
_CVS_DISTF${_i:N-}=	${SVN_DISTFILE${_i:N-}}-r${SVN_DISTREV${_i:N-}}.mcz
_CVS_FETCH${_i:N-}=	${MKSH} ${PORTSDIR}/infrastructure/scripts/mkmcz \
			    ${_MKMCZ_OPTS} -s \
			    ${FULLDISTDIR:Q}/${_CVS_DISTF${_i:N-}:Q} \
			    ${SVN_DISTPATH${_i:N-}:Q} \
			    ${SVN_DISTREV${_i:N-}:Q} \
			    ${SVN_DISTDIR${_i:N-}:Q}
_CVS_FDEP+=		mpczar svn
.  endif
.  if defined(_CVS_DISTF${_i:N-}) && (${MCZ_FETCH:L} == "xz")
_CVS_DISTF${_i:N-}:=	${_CVS_DISTF${_i:N-}}.xz
.  elif defined(_CVS_DISTF${_i:N-}) && (${MCZ_FETCH:L} == "lzma")
_CVS_DISTF${_i:N-}:=	${_CVS_DISTF${_i:N-}}.lzma
.  endif
.endfor

DIST_SOURCE?=		distfile
.if ${_CVS_FDEP:Mmpczar}
.  if ${MCZ_FETCH:L} == "no"
FETCH_DEPENDS+=		:mpczar->=20081101:archivers/mpczar
.  endif
DIST_SOURCE=		distfile
.  if defined(_CVS_DISTF)
DISTFILES=
.  endif
.endif
.if ${_CVS_FDEP:Msvn}
.  if ${MCZ_FETCH:L} == "no"
FETCH_DEPENDS+=		:subversion-*:devel/subversion
.  endif
.endif
.if ${DIST_SOURCE:L} == "port"
DIST_SOURCEDIR?=	${.CURDIR}/dist
.  if (${PERMIT_DISTFILES_CDROM:L} != "yes") || (${PERMIT_DISTFILES_FTP:L} != "yes")
ERRORS+=		"If using DIST_SOURCE=port the distfiles must be licenced appropriately."
ERRORS+=		"Please notify the MirPorts maintainer:"
ERRORS+=		"    ${RESPONSIBLE}"
_BAD_LICENCING=		Yes
.  endif
.elif ${DIST_SOURCE:L} == "module"
DIST_SOURCEDIR?=	${PORTSDIR}/Extras/${DIST_NAME}
.endif
.if ${DIST_SOURCE:L} != "distfile"
NO_CHECKSUM=		defined
NO_DISTFILES=		defined
.endif
EXTRACT_SUFX?=		.tar.gz
DISTFILES?=		${DISTNAME}${EXTRACT_SUFX}

_EVERYTHING=		${DISTFILES}
_DISTFILES=		${DISTFILES:C/:[0-9]$//}

.for _i in - 0 1 2 3 4 5 6 7 8 9
.  if defined(_CVS_DISTF${_i:N-})
_DISTFILES+=		${_CVS_DISTF${_i:N-}}
.  endif
.endfor

ALLFILES=		${_DISTFILES}

.if defined(PATCHFILES)
_PATCHFILES=		${PATCHFILES:C/:[0-9]$//}
_EVERYTHING+=		${PATCHFILES}
ALLFILES+=		${_PATCHFILES}
.endif

.if make(checksum) || make(makesum) || make(addsum) || defined(__FETCH_ALL)
.  if defined(SUPDISTFILES) && !defined(NOSUPDISTFILES)
_EVERYTHING+=		${SUPDISTFILES}
ALLFILES+=		${SUPDISTFILES:C/:[0-9]$//}
.  endif
.endif

__CKSUMFILES=
# First, remove duplicates
.for _file in ${ALLFILES}
.  if empty(__CKSUMFILES:M${_file})
__CKSUMFILES+=		${_file}
.  endif
.endfor
ALLFILES:=		${__CKSUMFILES}

.if defined(IGNOREFILES)
.  for _file in ${IGNOREFILES}
__CKSUMFILES:=		${__CKSUMFILES:N${_file}}
.  endfor
.endif

# List of all files, with ${DIST_SUBDIR} in front.  Used for checksum.
.if !empty(DIST_SUBDIR)
_CKSUMFILES=		${__CKSUMFILES:S/^/${DIST_SUBDIR}\//}
_IGNOREFILES=		${IGNOREFILES:S/^/${DIST_SUBDIR}\//}
.else
_CKSUMFILES=		${__CKSUMFILES}
_IGNOREFILES=		${IGNOREFILES}
.endif

# This is what is actually going to be extracted, and is overridable
#  by user.
EXTRACT_ONLY?=		${_DISTFILES}

# okay, time for some guess work
.if !empty(EXTRACT_ONLY:M*.bz2) || \
    !empty(EXTRACT_ONLY:M*.tbz) || !empty(EXTRACT_ONLY:M*.cbz) || \
    (defined(PATCHFILES) && !empty(_PATCHFILES:M*.bz2))
_USE_BZIP2?=		Yes
.endif
.if !empty(EXTRACT_ONLY:L:M*.l[zh][ha])
_USE_LHARC?=		Yes
.endif
.if !empty(EXTRACT_ONLY:M*.lzma)
_USE_LZMA?=		Yes
.endif
.if !empty(EXTRACT_ONLY:M*.xz) || \
    !empty(EXTRACT_ONLY:M*.txz) || !empty(EXTRACT_ONLY:M*.cxz)
_USE_XZ?=		Yes
.endif
.if !empty(EXTRACT_ONLY:M*.zip)
_USE_ZIP?=		Yes
.endif
_USE_BZIP2?=		No
_USE_LHARC?=		No
_USE_LZMA?=		No
_USE_XZ?=		No
_USE_ZIP?=		No

EXTRACT_CASES?=

_PERL_FIX_SHAR?=	perl -ne 'print if $$s || ($$s = m:^\#(\!\s*/bin/sh\s*| This is a shell archive):)'

# XXX note that we DON'T set EXTRACT_SUFX.

.if ${_USE_BZIP2:L} != "no"
BUILD_DEPENDS+=		:bzip2-*:archivers/bzip2
EXTRACT_CASES+=		\
    *.tar.bz2 | *.tbz | *.cpio.bz2 | *.cbz)				\
	${BZIP2} -dc ${FULLDISTDIR}/$$archive | ${TAR} xf - ;;		\
    *.bz2)								\
	${BZIP2} -dc ${FULLDISTDIR}/$$archive >$$(basename $$archive .bz2) ;;
.endif

.if ${_USE_LHARC:L} != "no"
BUILD_DEPENDS+=		:lha-*:archivers/lha
EXTRACT_CASES+=		\
    *.[Ll][Zz][Hh] | *.[Ll][Hh][Aa]) \
	lha xw=${WRKDIR}/${DISTNAME} ${FULLDISTDIR}/$$archive ;;
.endif

.if ${_USE_LZMA:L} != "no"
#BUILD_DEPENDS+=		:lzma-*:archivers/lzma
.  if !exists(/usr/bin/xzdec)
BUILD_DEPENDS+=		:xz-*:archivers/xz
.  endif
EXTRACT_CASES+=		\
    *.tar.lzma | *.cpio.lzma | *.mcz.lzma)				\
	lzmadec <${FULLDISTDIR}/$$archive | ${TAR} xf - ;;		\
    *.lzma)								\
	lzmadec <${FULLDISTDIR}/$$archive >$$(basename $$archive .lzma) ;;
.endif

.if ${_USE_XZ:L} != "no"
EXTRACT_CASES+=		\
    *.tar.xz | *.txz | *.cpio.xz | *.cxz | *.mcz.xz)			\
	xzdec <${FULLDISTDIR}/$$archive | ${TAR} xf - ;;		\
    *.xz)								\
	xzdec <${FULLDISTDIR}/$$archive >$$(basename $$archive .xz) ;;
.endif

.if ${_USE_ZIP:L} != "no"
BUILD_DEPENDS+=		:unzip-*:archivers/unzip
# stupid stupid stupid, LHarc extract caces do this right,
# but we cannot change the default to Yes now for compat…
_USE_ZIP_SUBDIR?=	No
.if ${_USE_ZIP_SUBDIR:L} == "no"
EXTRACT_CASES+=		\
    *.zip) \
	${UNZIP} -q ${FULLDISTDIR}/$$archive -d ${WRKDIR} ;;
.else
EXTRACT_CASES+=		\
    *.zip) \
	${UNZIP} -q ${FULLDISTDIR}/$$archive -d ${WRKDIR}/${DISTNAME} ;;
.endif
.endif

EXTRACT_CASES+=		\
    *.tar.gz | *.tar.[Zz] | *.t.gz | *.tgz | *.taz |			\
    *.cpio.gz | *.cpio.[Zz] | *.cgz | *.ngz | *.mcz)			\
	${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive | ${TAR} xf - ;;	\
    *.tar | *.cpio)							\
	${TAR} xf ${FULLDISTDIR}/$$archive ;;				\
    *.shar.gz | *.shar.[Zz] | *.sh.gz | *.sh.[Zz])			\
	${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive |			\
	    ${_PERL_FIX_SHAR} | ${SH} ;;				\
    *.shar | *.sh | *.shr)						\
	${_PERL_FIX_SHAR} ${FULLDISTDIR}/$$archive | ${SH} ;;		\
    *.gz | *.[Zz])							\
	${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive			\
	    >$$(basename $$archive .gz) ;;				\
    *.jar | *.pdf | *.txi)						\
	cp ${FULLDISTDIR}/$$archive ${WRKDIR}/ ;;			\
    *.uu.gz | *.uu.[Zz])						\
	${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive | uudecode ;;		\
    *.uu)								\
	uudecode ${FULLDISTDIR}/$$archive ;;				\
    *)									\
	${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive | ${TAR} xf - ;;


PATCH_CASES?=
.if ${_USE_BZIP2:L} != "no"
PATCH_CASES+=		*.bz2) ${BZIP2} -dc $$patchfile \
			    | ${PATCH} ${PATCH_DIST_ARGS} ;;
.endif
PATCH_CASES+=		*.Z|*.gz) ${GZCAT} $$patchfile \
			    | ${PATCH} ${PATCH_DIST_ARGS} ;;
PATCH_CASES+=		*) ${PATCH} ${PATCH_DIST_ARGS} <$$patchfile ;;

# Documentation
RESPONSIBLE?=		The MirPorts mailing list ${_MIRPORTS_ADDRESS}

.if !defined(CATEGORIES)
ERRORS+=		"Makefile variable CATEGORIES is mandatory."
.endif


CONFIGURE_SCRIPT?=	configure
.if ${CONFIGURE_SCRIPT:M/*}
_CONFIGURE_SCRIPT=	${CONFIGURE_SCRIPT}
.elif exists(${WRKSRC}/${CONFIGURE_SCRIPT})
_CONFIGURE_SCRIPT=	${WRKSRC}/${CONFIGURE_SCRIPT}
.else
_CONFIGURE_SCRIPT=	./${CONFIGURE_SCRIPT}
.endif

CONFIGURE_ENV+=		PATH=${PORTPATH:Q}
CONFIGURE_ENV+=		SHELL=${MKSH:Q} CONFIG_SHELL=${MKSH:Q}

.if ${NO_SHARED_LIBS:L} == "yes"
CONFIGURE_SHARED?=	--disable-shared
.else
CONFIGURE_SHARED?=	--enable-shared
.endif

# Passed to configure invocations, and user scripts
SCRIPTS_ENV+=		CURDIR=${.CURDIR:Q} DISTDIR=${DISTDIR:Q} \
			PATH=${PORTPATH:Q} WRKDIR=${WRKDIR:Q} \
			WRKDIST=${WRKDIST:Q} WRKSRC=${WRKSRC:Q} \
			WRKBUILD=${WRKBUILD:Q} PATCHDIR=${PATCHDIR:Q} \
			SCRIPTDIR=${SCRIPTDIR:Q} FILESDIR=${FILESDIR:Q} \
			PORTSDIR=${PORTSDIR:Q} DEPENDS=${DEPENDS:Q} \
			PREFIX=${PREFIX:Q} LOCALBASE=${LOCALBASE:Q} \
			X11BASE=${X11BASE:Q}

.if defined(BATCH)
SCRIPTS_ENV+=		BATCH=yes
.endif

FETCH_MANUALLY?=	No
.if (defined(_CVS_DISTF) && (${MCZ_FETCH:L} == "no")) || \
    (${FETCH_MANUALLY:L} != "no")
_ALLFILES_PRESENT=	Yes
.  for _F in ${ALLFILES:S@^@${FULLDISTDIR}/@}
.    if !exists(${_F})
_ALLFILES_PRESENT=	No
.    endif
.  endfor
.  if ${_ALLFILES_PRESENT:L} == "no"
IS_INTERACTIVE=		Yes
.  endif
.endif

################################################################
# Many ways to disable a port.
#
# If we're in BATCH mode and the port is interactive, or we're
# in interactive mode and the port is non-interactive, skip all
# the important targets.  The reason we have two modes is that
# one might want to leave a build in BATCH mode running
# overnight, then come back in the morning and do _only_ the
# interactive ones that required your intervention.
#
# Ignore ports that can't be resold if building for a CDROM.
#
# Don't build a port if it's broken.
#
# Don't build a port if it comes with the base system.
################################################################

.if defined(WANTLIB) || defined(MAINTAINER)
BROKEN+=		port not converted from OpenBSD to MirPorts
.endif

.if !defined(NO_IGNORE)
.  if (defined(REGRESS_IS_INTERACTIVE) && defined(BATCH))
_IGNORE_REGRESS=	"has interactive tests"
.  endif
.  if (!defined(REGRESS_IS_INTERACTIVE) && defined(INTERACTIVE))
_IGNORE_REGRESS=	"does not have interactive tests"
.  endif
.  if (defined(IS_INTERACTIVE) && defined(BATCH))
IGNORE+=		"is an interactive port"
.  endif
.  if (!defined(IS_INTERACTIVE) && defined(INTERACTIVE))
IGNORE+=		"is not an interactive port"
.  endif
.  if ${USE_X11:L} == "yes"
.    if !exists(${X11BASE})
IGNORE+=		"uses X11, but ${X11BASE} not found"
.    else
LDFLAGS+=		-Wl,--library-after=${X11BASE}/lib
.      if ${OBJECT_FMT} == "ELF"
LDFLAGS+=		-Wl,-rpath -Wl,${X11BASE}/lib
.      endif
.    endif
.  else
CONFIGURE_ENV+=		XMKMF=false
.  endif
.  if ${USE_CXX:L} == "yes" && ${NO_CXX:L} != "no"
IGNORE+=		"uses C++, but ${NO_CXX}"
.  endif
.  if defined(BROKEN)
IGNORE+=		"is marked as broken: ${BROKEN}"
.  endif
.  if defined(ONLY_FOR_PLATFORM)
__OK!=	ok=0; \
	set -o noglob; \
	for match in ${ONLY_FOR_PLATFORM}; do \
		saveIFS=$$IFS; \
		IFS=:; set -A s -- $$match; \
		IFS=$$saveIFS; \
		[[ $${s[0]} = @(\*|${OStype}) ]] || continue; \
		[[ $${s[2]} = @(\*|${ARCH}|${MACHINE_ARCH}) ]] || continue; \
		if [[ $${s[1]} = *.* ]]; then \
			saveIFS=$$IFS; \
			IFS=.; set -A sv -- $${s[1]}; \
			IFS=$$saveIFS; \
			(( $${sv[0]} <= ${OSver:R} )) || continue; \
			if (( $${sv[0]} == ${OSver:R} )); then \
				(( $${sv[1]} <= ${OSver:E} )) || continue; \
			fi; \
		else \
			[[ $${s[1]} = @(\*|${OSREV}) ]] || continue; \
		fi; \
		ok=1; \
		break; \
	done; \
	print $$ok
.    if ${__OK} == "0"
.      if ${ARCH} == ${MACHINE_ARCH}
IGNORE+=		"is only for ${ONLY_FOR_PLATFORM}, not ${OStype}:${OSver}:${ARCH}"
.      else
IGNORE+=		"is only for ${ONLY_FOR_PLATFORM}, not ${OStype}:${OSver}:${ARCH} (${MACHINE_ARCH})"
.      endif
.    endif
.    undef __OK
.  endif
.  if defined(NOT_FOR_PLATFORM)
__OK!=	ok=1; \
	set -o noglob; \
	test="${OStype}:${OSREV}:${ARCH} ${OStype}:${OSREV}:${MACHINE_ARCH}"; \
	for match in ${NOT_FOR_PLATFORM}; do \
		for platform in $$test; do \
			eval [[ $$platform != $$match ]] || ok=0; \
		done; \
	done; \
	print $$ok
.    if ${__OK} == "0"
IGNORE+=		"is not for ${NOT_FOR_PLATFORM}"
.    endif
.    undef __OK
.  endif
.endif		# NO_IGNORE


.if !defined(DEPENDS_TARGET)
.  if make(reinstall)
DEPENDS_TARGET=		reinstall
.  else
DEPENDS_TARGET=		install
.  endif
.endif

################################################################
# Dependency checking
################################################################

# Various dependency styles

_build_depends_fragment=	! ${PKG_CMD_INFO} -qe "$$pkg" || found=true
_run_depends_fragment=		${_build_depends_fragment}
_regress_depends_fragment=	${_build_depends_fragment}
_fetch_depends_fragment=	${_build_depends_fragment}

_resolve_lib_args=

.if ${NO_SHARED_LIBS:L} == "yes"
_resolve_lib_args:=	${_resolve_lib_args} -noshared
.endif

.if ${RTLD_TYPE} == "dyld"
_resolve_lib_args:=	${_resolve_lib_args} -dylib
.endif

.if ${RTLD_TYPE} == "GNU"
_resolve_lib_args:=	${_resolve_lib_args} -gnulib
.endif

_libresolve_fragment= \
	case "$$d" in \
	*/*)	shprefix="$${d%/*}/"; shdir="${LOCALBASE}/$${d%/*}"; \
		d=$${d\#\#*/};; \
	*)	shprefix=; shdir="${LOCALBASE}/lib";; \
	esac; \
	check=$$(eval $$listlibs | ${MKSH} \
	    ${PORTSDIR}/infrastructure/scripts/resolve-lib \
	    ${_resolve_lib_args} $$d) || true

_lib_depends_fragment= \
	what=$$dep; \
	whattype=' library'; \
	IFS=,; bad=false; for d in $$dep; do \
		listlibs='ls /usr/lib $$shdir 2>/dev/null'; \
		${_libresolve_fragment}; \
		case "$$check" in \
		Missing\ library) bad=true; msg="$$msg $$d missing...";; \
		Error:*) bad=true; msg="$$msg $$d unsolvable...";; \
		esac; \
	done; $$bad || ${_build_depends_fragment}

_FULL_PACKAGE_NAME?=	No

BUILD_DEPENDS+=		${B_R_DEPENDS}
RUN_DEPENDS+=		${B_R_DEPENDS}
.for _DEP in build run lib regress fetch
_DEP${_DEP}_COOKIES=
.  if defined(${_DEP:U}_DEPENDS) && !empty(${_DEP:U}_DEPENDS) && \
    ${NO_DEPENDS:L} == "no"
.    for _i in ${${_DEP:U}_DEPENDS}
_DEP${_DEP}_COOKIES+=	${WRKDIR}/.${_DEP}${_i:C,[|:./<=>*],-,g}
.    endfor
.  endif
.endfor

# Normal user-mode targets are PHONY targets, e.g., don't create the
# corresponding file. However, there is nothing phony about the cookie.

_INSTALL_DEPS=		${_INSTALL_COOKIE}
_PACKAGE_DEPS=		${_PACKAGE_COOKIES}
.if defined(ALWAYS_PACKAGE)
_INSTALL_DEPS+=		${_PACKAGE_COOKIES}
.endif
.if ${BULK_${PKGPATH}:L} == "yes"
_INSTALL_DEPS+=		${_BULK_COOKIE}
_PACKAGE_DEPS+=		${_BULK_COOKIE}
.endif
_UPGRADE_DEPS=
_UPGRADE_PKGS=

PREFER_SUBPKG_INSTALL?=	yes
.if empty(SUBPACKAGE) && defined(MULTI_PACKAGES) \
    && !empty(MULTI_PACKAGES) && (${PREFER_SUBPKG_INSTALL:L} == "yes")
.  for _i in ${MULTI_PACKAGES}
_INSTALL_DEPS+=		${PKG_DBDIR}/${FULLPKGNAME${_i}}/+CONTENTS
_UPGRADE_DEPS+=		_upgrade-${_i}
_UPGRADE_PKGS+=		${PKGFILE${_i}}

${PKG_DBDIR}/${FULLPKGNAME${_i}}/+CONTENTS: ${PKG_DBDIR}/${FULLPKGNAME}/+CONTENTS
	@env SUBPACKAGE=${_i:Q} ${MAKE} install-binpkg

_upgrade-${_i}:
	@env SUBPACKAGE=${_i:Q} ${MAKE} _upgrade
.  endfor
.endif

.if ${CONFIGURE_STYLE:L:Mbmake}
MAKE_ENV+=		CPPFLAGS=${CPPFLAGS:Q}
.endif

MODBMAKE_configure=	cd ${WRKBUILD} && \
			    exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
			    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE:Q} obj

MODBMAKE_pre_build=	cd ${WRKBUILD} && \
			    exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
			    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE:Q} depend

MODSIMPLE_configure=	cd ${WRKCONF} && \
			    ${_SYSTRACE_CMD} ${SETENV} \
			    ${MODSIMPLE_configure_env} \
			    ${SH} ${_CONFIGURE_SCRIPT} ${CONFIGURE_ARGS}

MODSIMPLE_USE_INSTALL?=	${INSTALL} -c -o ${BINOWN} -g ${BINGRP}
MODSIMPLE_configure_env=REALOS=${OStype:Q} MKSH=${MKSH:Q} \
			ac_cv_path_CC=${_PASS_CC:T:Q} ac_cv_path_CXX=${_PASS_CXX:T:Q} \
			CC=${_PASS_CC:T:Q} CFLAGS="$$(print -nr -- ${CFLAGS:Q} | \
			    sed -e 's${CPPFLAGS:S\\\\\\g}g' \
			    -e 's/[ 	]*$$//')" \
			CXX=${_PASS_CXX:T:Q} CXXFLAGS="$$(print -nr -- ${CXXFLAGS:Q} | \
			    sed -e 's${CPPFLAGS:S\\\\\\g}g' \
			    -e 's/[ 	]*$$//')" \
			LD=${LD:Q} LDFLAGS=${LDFLAGS:Q} CPPFLAGS=${CPPFLAGS:Q} \
			INSTALL=${MODSIMPLE_given_INSTALL:Q} \
			ac_given_INSTALL=${MODSIMPLE_given_INSTALL:Q} \
			INSTALL_SCRIPT=${INSTALL_SCRIPT:Q} \
			INSTALL_PROGRAM=${INSTALL_PROGRAM:Q} YACC=${YACC:Q} \
			INSTALL_MAN=${INSTALL_MAN:Q} GCC_NO_WERROR=1 \
			INSTALL_DATA=${INSTALL_DATA:Q} ${CONFIGURE_ENV}

_FAKE_SETUP=		TRUEPREFIX=${PREFIX:Q} PREFIX=${WRKINST:Q}${PREFIX:Q} \
			${DESTDIRNAME}=${WRKINST:Q}

VMEM_WARNING?=		No
VMEM_AUTOUNLOCK?=	No
_CLEANDEPENDS?=		Yes

_VMEM_UNLOCK:=
.if (${VMEM_AUTOUNLOCK:L} == "yes") && (${VMEM_WARNING:L} == "yes")
_VMEM_UNLOCK+=		${_VMEM_UNLOCK_CMDS}
.endif

# mirroring utilities
.if !empty(DIST_SUBDIR)
_ALLFILES=		${ALLFILES:S/^/${DIST_SUBDIR}\//}
.else
_ALLFILES=		${ALLFILES}
.endif

_FMN=			${PKGPATH}/${FULLPKGNAME}
.if defined(MULTI_PACKAGES)
.  for _S in ${MULTI_PACKAGES}
_FMN+=			${PKGPATH}/${FULLPKGNAME${_S}}
.  endfor
.endif

# Internal variables, used by dependencies targets
# Only keep pkg:dir spec
.if defined(LIB_DEPENDS) && !empty(LIB_DEPENDS) && ${NO_SHARED_LIBS:L} != "yes"
_ALWAYS_DEP2=		${LIB_DEPENDS:C/^[^:]*:([^:]*:[^:]*).*$/\1/}
_ALWAYS_DEP=		${_ALWAYS_DEP2:C/[^:]*://}
.else
_ALWAYS_DEP2=
_ALWAYS_DEP=
.endif

.if defined(RUN_DEPENDS) && !empty(RUN_DEPENDS)
_RUN_DEP2=		${RUN_DEPENDS:C/^[^:]*:([^:]*:[^:]*).*$/\1/}
_RUN_DEP=		${_RUN_DEP2:C/[^:]*://}
.else
_RUN_DEP2=
_RUN_DEP=
.endif

.if defined(BUILD_DEPENDS) && !empty(BUILD_DEPENDS)
_BUILD_DEP2=		${BUILD_DEPENDS:C/^[^:]*:([^:]*:[^:]*).*$/\1/}
_BUILD_DEP=		${_BUILD_DEP2:C/[^:]*://}
.else
_BUILD_DEP2=
_BUILD_DEP=
.endif

.if defined(FETCH_DEPENDS) && !empty(FETCH_DEPENDS)
_FETCH_DEP2=		${FETCH_DEPENDS:C/^[^:]*:([^:]*:[^:]*).*$/\1/}
_FETCH_DEP=		${_FETCH_DEP2:C/[^:]*://}
.else
_FETCH_DEP2=
_FETCH_DEP=
.endif

_LIB_DEP2=		${LIB_DEPENDS}
README_NAME?=		${TEMPLATES}/README.port

REORDER_DEPENDENCIES?=

.if defined(_STAT_SIZE)
_size_fragment=		stat -f 'SIZE (%N) = %z' $$file || echo -1
.elif ${HAS_CKSUM:L} == "yes"
_size_fragment=		${CKSUM_CMD} -a size $$file || echo -1
.else
_size_fragment=		print "SIZE ($$file) =" $$(wc -c <"$$file" || echo -1)
.endif

###
### end of variable setup. Only targets now
###

${LOCALBASE}/db/fake.mtree: ${PORTSDIR}/infrastructure/templates/fake.mtree
	${SUDO} cp $> $@
	if [[ ${BINOWN} != root ]]; then \
		print 'g/[ug]name=[a-z]*/s///g\n'"/^.set/s/   /" \
		    "uname=@BINOWN@ gname=@BINGRP@ /\nwq" \
		    | ${SUDO} ed -s $@; \
	fi

.if ${BIN_PACKAGES:L} == "yes"
${_PACKAGE_COOKIE}:
	@cd ${.CURDIR} && exec ${MAKE} ${_PACKAGE_COOKIE_DEPS}
.else
${_PACKAGE_COOKIE}: ${_PACKAGE_COOKIE_DEPS}
.endif
	@cd ${.CURDIR} && SUBPACKAGE= FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING= exec ${MAKE} _package
.if !defined(PACKAGE_NOINSTALL)
	@${_MAKE_COOKIE} $@
.endif

.for _s in ${MULTI_PACKAGES}
.  if ${BIN_PACKAGES:L} == "yes"
${_PACKAGE_COOKIE${_s}}:
	@cd ${.CURDIR} && exec ${MAKE} ${_PACKAGE_COOKIE_DEPS}
.  else
${_PACKAGE_COOKIE${_s}}: ${_PACKAGE_COOKIE_DEPS}
.  endif
	@cd ${.CURDIR} && SUBPACKAGE=${_s:Q} FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING=${_s:Q} exec ${MAKE} _package
.endfor

.PRECIOUS: ${_PACKAGE_COOKIES} ${_INSTALL_COOKIE}

${_SYSTRACE_COOKIE}:
	@rm -f $@
.for _i in ${_SYSTRACE_POLICIES}
	@echo "Policy: ${_i}, Emulation: native" >>$@
	@if [ -f ${.CURDIR}/systrace.filter ]; then \
		cat ${.CURDIR}/systrace.filter >>$@; \
	fi
	@sed ${_SYSTRACE_SED_SUBST} ${SYSTRACE_FILTER} >>$@
.  if ${USE_CCACHE:L} == "yes"
	@for cmd in chmod chown fswrite lchown link mknod rename symlink; do \
		print '\tnative-'$$cmd: filename match \
		    \"${CCACHE_DIR:Q}\" then permit; \
	done >>$@
.  endif
.endfor
	@if [ -f ${.CURDIR}/systrace.policy ]; then \
		sed ${_SYSTRACE_SED_SUBST} ${.CURDIR}/systrace.policy >>$@; \
	fi

# create the packing stuff from source
${WRKPKG}/COMMENT${SUBPACKAGE}:
	@echo ${_COMMENT:Q} >$@

${WRKPKG}/PLIST${SUBPACKAGE}: ${PLIST} ${WRKPKG}/depends${SUBPACKAGE}
	echo "@comment subdir=${FULLPKGPATH}" \
	    "cdrom=${PERMIT_PACKAGE_CDROM:L:S/"/\"/g}" \
	    "ftp=${PERMIT_PACKAGE_FTP:L:S/"/\"/g}" \
	    >$@.tmp
.if ${PERMIT_PACKAGE_CDROM:L} == "yes"
	echo "@comment @tag permit cdrom" >>$@.tmp
.endif
.if ${PERMIT_PACKAGE_FTP:L} == "yes"
	echo "@comment @tag permit ftp" >>$@.tmp
.endif
	echo "@comment @tag cc ${USE_COMPILER:L}" >>$@.tmp
.if ${NO_CXX:L} == "no"
	echo "@comment @tag dep cxx yes" >>$@.tmp
.endif
.if ${USE_X11:L} == "yes"
	echo "@comment @tag dep x11" >>$@.tmp
.endif
	echo "@comment" \
	    "portdir=http://cvs.mirbsd.de/ports/${PKGPATH}/" \
	    >>$@.tmp
	sort -u <${WRKPKG}/depends${SUBPACKAGE} >>$@.tmp
.if ${NO_SHARED_LIBS:L} == "yes"
	sed -e '/^!%%SHARED%%$$/r${PKGDIR}/PFRAG.no-shared${SUBPACKAGE}' \
	    -e '//d' \
	    -e '/^%%!SHARED%%$$/r${PKGDIR}/PFRAG.no-shared${SUBPACKAGE}' \
	    -e '//d' -e '/^%%SHARED%%$$/d' <${PLIST} ${SED_PLIST} >>$@.tmp
.elif ${OBJECT_FMT} == "Mach-O"
	if [ -e ${PKGDIR}/PFRAG.dylib${SUBPACKAGE} ]; then \
		sed -e '/^!%%SHARED%%$$/d' \
		    -e '/^%%!SHARED%%$$/d' \
		    -e '/^%%SHARED%%$$/r${PKGDIR}/PFRAG.dylib${SUBPACKAGE}' \
		    -e '//d' <${PLIST} ${SED_PLIST} \
		    >>$@.tmp; \
	else \
		echo '@option dylib' >>$@.tmp; \
		sed -e '/^!%%SHARED%%$$/d' \
		    -e '/^%%!SHARED%%$$/d' \
		    -e '/^%%SHARED%%$$/r${PKGDIR}/PFRAG.shared${SUBPACKAGE}' \
		    -e '//d' <${PLIST} ${SED_PLIST} \
		    >>$@.tmp; \
	fi
.elif ${OStype} == "Interix"
	echo '@option gnu-ld' >>$@.tmp; \
	sed -e '/^!%%SHARED%%$$/d' -e '/^%%!SHARED%%$$/d' \
	    -e '/^%%SHARED%%$$/r${PKGDIR}/PFRAG.shared${SUBPACKAGE}' \
	    -e '//d' <${PLIST} ${SED_PLIST} >>$@.tmp
.else
	echo '@option ldcache' >>$@.tmp; \
	sed -e '/^!%%SHARED%%$$/d' -e '/^%%!SHARED%%$$/d' \
	    -e '/^%%SHARED%%$$/r${PKGDIR}/PFRAG.shared${SUBPACKAGE}' \
	    -e '//d' <${PLIST} ${SED_PLIST} >>$@.tmp
.endif
	mv $@.tmp $@

${WRKPKG}/depends${SUBPACKAGE}:
	@mkdir -p ${WRKPKG}
	@>$@
.if (defined(RUN_DEPENDS) && !empty(RUN_DEPENDS)) || \
    (${NO_SHARED_LIBS:L} != "yes" && \
     defined(LIB_DEPENDS) && !empty(LIB_DEPENDS))
	@${_depfile_fragment}; \
	    echo "|${FULLPKGNAME${SUBPACKAGE}}|" >>$${_DEPENDS_FILE}; \
	    self=${FULLPKGNAME${SUBPACKAGE}} _depends_result=$@ \
	    ${MAKE} _recurse-solve-package-depends
.endif

${WRKPKG}/DESCR${SUBPACKAGE}: ${DESCR}
	@${_SED_SUBST} <$? >$@.tmp && mv -f $@.tmp $@
	@echo "\nMaintainer: ${RESPONSIBLE}" >>$@
.if defined(HOMEPAGE)
	@fgrep -q '$${HOMEPAGE}' $? || echo "\nWWW: "${HOMEPAGE:Q} >>$@
.endif
.if !empty(FLAVOURS)
	@echo "\nFlavours available:" ${FLAVOURS} >>$@
.endif

${WRKPKG}/mtree.spec: ${MTREE_FILE}
	@${_SED_SUBST} ${MTREE_FILE} >$@.tmp
	@(print '/@@local/d\ni\n'; IFS=/; s=; \
	 for pc in $$(print ${LOCALBASE:Q}); do \
		s="$$s    "; print "$$s$$pc"; \
	 done; \
	 print .; \
	 print '%g/@BINOWN@/s//${BINOWN}/g'; \
	 print '%g/@BINGRP@/s//${BINGRP}/g'; \
	 print wq) | ed -s $@.tmp
	@mv -f $@.tmp $@

# substitute
.for _subst_file in INSTALL DEINSTALL REQ
.  if exists(${PKGDIR}/${_subst_file}${SUBPACKAGE})
${WRKPKG}/${_subst_file}${SUBPACKAGE}: ${PKGDIR}/${_subst_file}${SUBPACKAGE}
	@${_SED_SUBST} <$? >$@.tmp && mv -f $@.tmp $@
.  endif
.endfor

.if defined(MESSAGE)
${WRKPKG}/MESSAGE${SUBPACKAGE}: ${MESSAGE}
	@${_SED_SUBST} <$? >$@.tmp && mv -f $@.tmp $@
.endif

makesum: fetch-all
.if !defined(NO_CHECKSUM)
	@rm -f ${CHECKSUM_FILE}
	@cd ${DISTDIR} && ${CKSUM_CMD} ${_CIPHERS:S/^/-a /} -a size \
	    ${_CKSUMFILES} >>${CHECKSUM_FILE}
	@for file in ${_IGNOREFILES}; do \
		echo "MD5 ($$file) = IGNORE" >>${CHECKSUM_FILE}; \
	done
	@sort -u -o ${CHECKSUM_FILE} ${CHECKSUM_FILE}
	@print '1i\n$$Mir''OS$$\n\n.\nwq' | ed -s ${CHECKSUM_FILE}
.endif

addsum: fetch-all
.if !defined(NO_CHECKSUM)
	@touch ${CHECKSUM_FILE}
	@cd ${DISTDIR} && ${CKSUM_CMD} ${_CIPHERS:S/^/-a /} -a size \
	    ${_CKSUMFILES} >>${CHECKSUM_FILE}
	@for file in ${_IGNOREFILES}; do \
		echo "MD5 ($$file) = IGNORE" >>${CHECKSUM_FILE}; \
	done
	@sort -u -o ${CHECKSUM_FILE} ${CHECKSUM_FILE}
	@if [ $$(sed -e 's/\=.*$$//' ${CHECKSUM_FILE} | uniq -d | \
	    wc -l) -ne 0 ]; then \
		echo "Inconsistent checksum in ${CHECKSUM_FILE}"; \
		exit 1; \
	else \
		${ECHO_MSG} "${CHECKSUM_FILE} updated okay," \
		    "don't forget to remove cruft"; \
	fi
.endif


################################################################
# Dependency checking
################################################################

depends: lib-depends build-depends run-depends regress-depends

# and the rules for the actual dependencies

_print-packagename:
.if ${_FULL_PACKAGE_NAME:L} == "yes"
	@echo ${PKGPATH:Q}/${FULLPKGNAME${SUBPACKAGE}:Q}
.else
	@echo ${FULLPKGNAME${SUBPACKAGE}}
.endif

.for _DEP in build run lib regress fetch
.  if defined(${_DEP:U}_DEPENDS) && !empty(${_DEP:U}_DEPENDS) && \
    ${NO_DEPENDS:L} == "no"
.    for _i in ${${_DEP:U}_DEPENDS}
${WRKDIR}/.${_DEP}${_i:C,[|:./<=>*],-,g}: ${_WRKDIR_COOKIE}
	@unset PACKAGING DEPENDS_TARGET FLAVOUR SUBPACKAGE \
	    _MASTER WRKDIR|| true; \
	echo ${_i:Q}|{ \
		IFS=:; read dep pkg dir target; \
		${_flavour_fragment}; defaulted=false; \
		case "X$$target" in X) target=${DEPENDS_TARGET};; esac; \
		case "X$$target" in \
		Xinstall|Xreinstall) early_exit=false;; \
		Xpackage) early_exit=true;; \
		*) \
			early_exit=true; mkdir -p ${WRKDIR}/$$dir; \
			toset="$$toset \
			    _MASTER='[${FULLPKGNAME${SUBPACKAGE}}]${_MASTER}' \
			    WRKDIR=${WRKDIR}/$$dir"; \
			dep="/nonexistent";; \
		esac; \
		case "X$$pkg" in \
		X)	pkg=$$(eval $$toset ${MAKE} _print-packagename | sed -e 's,-[0-9].*,-*,'); \
			defaulted=true;; \
		esac; \
		for abort in false false true; do \
			if $$abort; then \
				${ECHO_MSG} "Dependency check failed"; \
				exit 1; \
			fi; \
			found=false; \
			what=$$pkg; \
			whattype=; \
			case "$$dep" in \
			"/nonexistent") ;; \
			*)  \
				${_${_DEP}_depends_fragment}; \
				if $$found; then \
					${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} depends on: $$what$$whattype - found"; \
					break; \
				else \
					: $${msg:= not found}; \
					${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} depends on: $$what$$whattype -$$msg"; \
				fi;; \
			esac; \
			if [[ -z $$dir ]]; then \
				${ECHO_MSG} "===>  Please install $$what manually."; \
				${ECHO_MSG} "      There is no MirPort available for this dependency."; \
				exit 1; \
			fi; \
			${ECHO_MSG} "===>  Verifying $$target for $$what in $$dir"; \
			[[ $$target = *patch* ]] && \
			    target="__AUTOPORT_RECURSIVE=1 $$target"; \
			if eval $$toset ${MAKE} $$target; then \
				${ECHO_MSG} "===> Returning to build of ${FULLPKGNAME${SUBPACKAGE}}${_MASTER}"; \
			else \
				exit 1; \
			fi; \
			if $$early_exit; then \
				break; \
			fi; \
		done; \
	}
	@${_MAKE_COOKIE} $@
.    endfor
.  endif
${_DEP}-depends: ${_DEP${_DEP}_COOKIES}

whatif-${_DEP}-depends: .PHONY
.  if defined(${_DEP:U}_DEPENDS) && !empty(${_DEP:U}_DEPENDS) && \
    ${NO_DEPENDS:L} == "no"
.    for _i in ${${_DEP:U}_DEPENDS}
	@unset PACKAGING DEPENDS_TARGET FLAVOUR SUBPACKAGE \
	    _MASTER WRKDIR|| true; \
	echo ${_i:Q}|{ \
		IFS=:; read dep pkg dir target; \
		${_flavour_fragment}; defaulted=false; \
		case "X$$target" in X) target=${DEPENDS_TARGET};; esac; \
		case "X$$target" in \
		Xinstall|Xreinstall) early_exit=false;; \
		Xpackage) early_exit=true;; \
		*) \
			early_exit=true; mkdir -p ${WRKDIR}/$$dir; \
			toset="$$toset \
			    _MASTER='[${FULLPKGNAME${SUBPACKAGE}}]${_MASTER}' \
			    WRKDIR=${WRKDIR}/$$dir"; \
			dep="/nonexistent";; \
		esac; \
		case "X$$pkg" in \
		X)	pkg=$$(eval $$toset ${MAKE} _print-packagename | sed -e 's,-[0-9].*,-*,'); \
			defaulted=true;; \
		esac; \
		for abort in x; do \
			found=false; \
			what=$$pkg; \
			whattype=; \
			case "$$dep" in \
			"/nonexistent") ;; \
			*)  \
				${_${_DEP}_depends_fragment}; \
				if $$found; then \
					${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} depends on: $$what$$whattype - found"; \
					break; \
				else \
					: $${msg:= not found}; \
					${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} depends on: $$what$$whattype -$$msg"; \
				fi;; \
			esac; \
			if [[ -z $$dir ]]; then \
				${ECHO_MSG} "===>  Please install $$what manually."; \
				${ECHO_MSG} "      There is no MirPort available for this dependency."; \
				exit 1; \
			fi; \
			${ECHO_MSG} "===>  Verifying $$target for $$what in $$dir"; \
			eval $$toset ${MAKE} whatif-depends; \
		done; \
	}
.    endfor
.  endif
.endfor

whatif-depends: .PHONY whatif-fetch-depends whatif-build-depends \
    whatif-lib-depends whatif-run-depends #whatif-regress-depends

# Do a brute-force ldd/objdump on all files under WRKINST.
_CHECK_LIBS_SCRIPT=	${PORTSDIR}/infrastructure/scripts/check-libs-elf
${_LIBLIST}: ${_FAKE_COOKIE}
	@cd ${WRKINST} && ${SUDO} find . -type f|\
		${SUDO} xargs objdump -p 2>/dev/null |\
		sed -n \
		    -e '/^ *NEEDED *\(.*\)\.so\.\([0-9][0-9]*\)\.\([0-9][0-9]*\)$$/s//\1 \2 \3/p' \
		    -e '/^ *NEEDED *\(.*\)\.so$$/s//\1/p' \
		| sort -u >$@

# list of libraries that can be used: libraries just built, and system libs.
${_BUILDLIBLIST}: ${_FAKE_COOKIE}
	@{ \
		${SUDO} find ${WRKINST} -type f -o -type l; \
		find /usr/lib -path /usr/lib -o -type d -prune \
		    -o -type f -print; \
		find ${X11BASE}/lib -path ${X11BASE}/lib -o -type d -prune \
		    -o -type f -print; \
	} | \
		egrep '(\.so\.|\.so$$)' | ${SUDO} xargs file -L \
		    | fgrep 'shared' | cut -d\: -f1 | sort -u >$@


.for _i in ${EMUL}
.  ifndef HAS_EMUL_${_i}
HAS_EMUL_${_i}!=sysctl -n kern.emul.${_i} 2>/dev/null
.    if ${__MAKEFLAGS_HACKERY:L} == "yes"
.MAKEFLAGS:=	${.MAKEFLAGS} HAS_EMUL_${_i}=${HAS_EMUL_${_i}:Q}
.    endif
.  endif
.  if ${HAS_EMUL_${_i}} != "1"
IGNORE+=	"needs ${_i} emulation, which is turned off, see compat_${_i}(8)"
.  endif
.endfor


.if defined(IGNORE) && !defined(NO_IGNORE)
fetch checksum extract patch configure all build install regress \
    uninstall deinstall fake package lib-depends-check manpages-check \
    relevant-checks whatif-depends:
.  if !defined(IGNORE_SILENT)
.    for _i in ${IGNORE}
	@${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} "${_i}.
.    endfor
.  endif

.else
# For now, just check all libnames are present
# The check is done on the fake area, be wary of multi-packages situation,
# since we don't take it into account yet.
#
# Note that we cache needed library names, and libraries we're allowed to
# depend upon, but not the actual list of lib depends, since this list is
# going to be tweaked as a result of running lib-depends-check.
#
lib-depends-check: ${_LIBLIST} ${_BUILDLIBLIST}
	@${_depfile_fragment}; \
	LIB_DEPENDS="$$(${MAKE} _recurse-lib-depends-check)" \
	PKG_DBDIR=${PKG_DBDIR:Q} perl ${_CHECK_LIBS_SCRIPT} \
	    ${_LIBLIST} ${_BUILDLIBLIST}

manpages-check: ${_FAKE_COOKIE}
	@cd ${WRKINST}${TRUEPREFIX}/man && \
	    ${SUDO} /usr/libexec/makewhatis -p . && cat whatis.db

# Most standard port targets create a cookie to avoid being re-run.
#
# fetch is an exception, as it uses the files it fetches as 'cookies',
# and it's run by checksum, so in essence it's a sub-goal of extract,
# in normal use.
#
# Besides, fetch can't create cookies, as it does not have WRKDIR available
# in the first place.
#
# IMPORTANT: pre-fetch/do-fetch/post-fetch MUST be designed so that they
# can be run several times in a row.

.ifdef NO_DISTFILES
DISTFILES=
.endif

fetch:
.  ifndef NO_DISTFILES
	@${ECHO_MSG} "===>  Checking files for ${FULLPKGNAME}${_MASTER}"
.    if target(pre-fetch)
	@cd ${.CURDIR} && exec ${MAKE} pre-fetch
.    endif
.    if target(do-fetch)
	@cd ${.CURDIR} && exec ${MAKE} do-fetch
.    else
# What FETCH normally does:
.      if !empty(ALLFILES)
	@cd ${.CURDIR} && exec ${MAKE} ${ALLFILES:S@^@${FULLDISTDIR}/@}
.      endif
# End of FETCH
.    endif
.    if target(post-fetch)
	@cd ${.CURDIR} && exec ${MAKE} post-fetch
.    endif
.  endif


checksum: fetch
	@-cd ${DISTDIR} && rm -f ${_CKSUMFILES:S!^!{CDROM,FTP}/!} 2>/dev/null
.  if !defined(NO_CHECKSUM) && !empty(_CKSUMFILES)
	@checksum_file=${CHECKSUM_FILE}; \
	if [ ! -f $$checksum_file ]; then \
		${ECHO_MSG} ">> No checksum file."; \
	else \
		if [[ ! -e ${WRKDIR}/.sums ]]; then \
			mkdir -p ${WRKDIR}; \
			(cd ${DISTDIR}; \
			if [[ ${HAS_CKSUM:L} == no ]]; then \
				${CKSUM_CMD} ${_CKSUMFILES}; \
			elif [[ ${HAS_CKSUM:L} == @(old|md) ]]; then \
				cksum ${_CKSUMFILES}; \
				md5 ${_CKSUMFILES}; \
				[[ ${HAS_CKSUM:L} == md ]] || \
				    rmd160 ${_CKSUMFILES}; \
			else \
				${CKSUM_CMD} \
				    ${_CIPHERS:S/^/-a /} ${_CKSUMFILES}; \
			fi) >${WRKDIR}/.sums; \
		fi; \
		cd ${DISTDIR}; OK=true; list=; \
		case ${HAS_CKSUM:L} { \
		(md)	allciphers="cksum md5" ;; \
		(no)	allciphers="cksum" ;; \
		(old)	allciphers="cksum md5 rmd160" ;; \
		(yes)	allciphers="${_CIPHERS}" ;; \
		}; \
		for file in ${_CKSUMFILES}; do \
			match=; \
			for cipher in $$allciphers; do \
				if [[ $$cipher = cksum ]]; then \
					s=$$(grep "$$file\$$" \
					    $$checksum_file || true); \
					if [[ -z $$s ]]; then \
						${ECHO_MSG} ">> No cksum recorded for $$file."; \
						continue; \
					fi; \
					t=$$(grep "$$file\$$" \
					    ${WRKDIR}/.sums || true); \
					if [[ $$s = $$t ]]; then \
						match=1; \
						${ECHO_MSG} ">> cksum OK for $$file."; \
					else \
						echo ">> cksum mismatch for $$file."; \
						OK=false; \
					fi; \
					continue; \
				fi; \
				set -- $$(grep -i "^$$cipher ($$file)" \
				    $$checksum_file); \
				if (( !$$# )); then \
					${ECHO_MSG} ">> No $$cipher checksum recorded for $$file."; \
					continue; \
				fi; \
				case $$4 in \
				"") \
					${ECHO_MSG} ">> No checksum recorded for $$file."; \
					OK=false;; \
				IGNORE) \
					echo ">> Checksum for $$file is set to IGNORE in md5 file even though"; \
					echo "   the file is not in the "'$$'"{IGNOREFILES} list."; \
					OK=false;; \
				*) \
					CKSUM=$$(grep -i "^$$cipher ($$file)" \
					    ${WRKDIR}/.sums | sed 's/^.*= //'); \
					case $$CKSUM in \
				  	"$$4") \
						match=1; \
						${ECHO_MSG} ">> Checksum OK for $$file. ($$cipher)";; \
					*) \
						echo ">> Checksum mismatch for $$file. ($$cipher)"; \
						if [[ -n $$_CKSUM_DEBUG ]]; then \
							echo "<< HAVE '$$CKSUM'"; \
							echo "<< WANT '$$4'"; \
						fi; \
						list="$$list $$file $$cipher $$4"; \
						OK=false;; \
					esac;; \
				esac; \
			done; \
			[[ $$match = 1 ]] || OK=false; \
		done; \
		set --; \
		for file in ${_IGNOREFILES}; do \
		  set -- $$(grep "($$file)" $$checksum_file) || \
			  { echo ">> No checksum recorded for $$file, file is in "'$$'"{IGNOREFILES} list." && \
			  OK=false; } ; \
		  case $$4 in \
		  	IGNORE) : ;; \
			*) \
			  echo ">> Checksum for $$file is not set to IGNORE in md5 file even though"; \
			  echo "   the file is in the "'$$'"{IGNOREFILES} list."; \
			  OK=false;; \
		  esac; \
		done; \
		if ! $$OK; then \
		  rm -f ${WRKDIR}/.sums; \
		  if ${REFETCH}; then \
		  	cd ${.CURDIR} && ${MAKE} _refetch _PROBLEMS="$$list"; \
		  else \
			echo "Make sure the Makefile and checksum file ($$checksum_file)"; \
			echo "are up to date.  If you want to fetch a good copy of this"; \
			echo "file from the OpenBSD or MirOS main archive, type"; \
			echo "\"mmake REFETCH=true [other args]\"."; \
			exit 1; \
		  fi; \
		fi ; \
  fi
.  endif
.  if (${PERMIT_DISTFILES_FTP:L} == "yes") && !empty(_CKSUMFILES)
	@cd ${DISTDIR}; all=; for i in ${_CKSUMFILES:H}; do \
		[[ " $$all " = *" $$i "* ]] || all="$$all $$i"; \
	done; \
	mkdir -p CDROM FTP; \
	(cd CDROM; mkdir -p $$all); \
	(cd FTP; mkdir -p $$all); \
	for i in $$all; do \
		if [[ ! -w $$i || ! -w CDROM/$$i || ! -w FTP/$$i ]]; then \
			print -u2 'Warning: some subdirectory of ${DISTDIR}' \
			    'is not writable for you!'; \
			break; \
		fi; \
	done
.    if ${PERMIT_DISTFILES_CDROM:L} == "yes"
.      for _i in ${_CKSUMFILES}
	@[[ -e ${DISTDIR}/CDROM/${_i} ]] || \
	    [[ ! -e ${DISTDIR}/${_i} ]] || \
	    ln ${DISTDIR}/${_i} ${DISTDIR}/CDROM/${_i} 2>&- || \
	    ln -s ${DISTDIR}/${_i} ${DISTDIR}/CDROM/${_i}
.      endfor
.    endif
.    for _i in ${_CKSUMFILES}
	@[[ -e ${DISTDIR}/FTP/${_i} ]] || \
	    [[ ! -e ${DISTDIR}/${_i} ]] || \
	    ln ${DISTDIR}/${_i} ${DISTDIR}/FTP/${_i} 2>&- || \
	    ln -s ${DISTDIR}/${_i} ${DISTDIR}/FTP/${_i}
.    endfor
.  endif

_refetch:
.  ifndef NO_DISTFILES
.    for file cipher value in ${_PROBLEMS}
	@rm ${DISTDIR}/${file}
	@cd ${.CURDIR} && exec ${MAKE} ${DISTDIR}/${file} \
	    MASTER_SITE_OVERRIDE="ftp://ftp.openbsd.org/pub/OpenBSD/distfiles/${cipher}/${value}/"
.    endfor
	cd ${.CURDIR} && exec ${MAKE} checksum REFETCH=false
.  endif


# The cookie's recipe hold the real rule for each of those targets.

extract: ${_EXTRACT_COOKIE}
patch: ${_DEPbuild_COOKIES} ${_DEPlib_COOKIES} \
	${_PATCH_COOKIE}
distpatch: ${_DEPbuild_COOKIES} ${_DEPlib_COOKIES} \
	${_DISTPATCH_COOKIE}
configure: ${_DEPbuild_COOKIES} ${_DEPlib_COOKIES} \
	${_CONFIGURE_COOKIE}
all build: ${_DEPbuild_COOKIES} ${_DEPlib_COOKIES} \
	${_BUILD_COOKIE}
install: ${_INSTALL_DEPS}
fake: ${_FAKE_COOKIE}
package: ${_PACKAGE_DEPS}

unconfigure:
	rm -f ${_CONFIGURE_COOKIE}

.  if defined(_IGNORE_REGRESS)
regress:
.    if !defined(IGNORE_SILENT)
	@${ECHO_MSG} "===>  ${FULLPKGNAME${SUBPACKAGE}}${_MASTER} ${_IGNORE_REGRESS}."
.    endif
.  else
regress: ${_DEPregress_COOKIES} ${_REGRESS_COOKIE}
.  endif

.endif # IGNORECMD

${_BULK_COOKIE}: ${_PACKAGE_COOKIES}
	@mkdir -p ${BULK_COOKIES_DIR}
.for _i in ${BULK_TARGETS_${PKGPATH}}
	@${ECHO_MSG} "===> Running ${_i}"
	@cd ${.CURDIR} && exec ${MAKE} ${_i} ${BULK_FLAGS}
.endfor
	@cd ${.CURDIR} && exec ${SUDO} ${MAKE} clean
	@${_MAKE_COOKIE} $@

# The real targets. Note that some parts always get run, some parts can be
# disabled, and there are hooks to override behavior.

.if (${MACHINE_OS} == "Darwin") || (${OStype} == "MidnightBSD")
${_WRKDIR_COOKIE}: ${LOCALBASE}/db/specs.${_ORIG_CC:S!/!_!g}
.else
${_WRKDIR_COOKIE}:
.endif
	@rm -rf ${WRKDIR}
	@mkdir -p ${WRKDIR} ${WRKDIR}/bin
	@ln -s ${_MIRMAKE_EXE} ${WRKDIR}/bin/make
	@print '#!'${MKSH:Q}'\nexec' ${_USE_CC:Q} ${_USE_CCSTD} '"$$@"' >${WRKDIR}/bin/${_MPWRAP_CC}
.if ${NO_CXX:L} != "no"
	@print '#!'${MKSH:Q}'\nexit 1' >${WRKDIR:Q}/bin/${_MPWRAP_CXX}
.else
	@print '#!'${MKSH:Q}'\nexec' ${_USE_CXX:Q} ${_USE_CXXSTD} '"$$@"' >${WRKDIR}/bin/${_MPWRAP_CXX}
.endif
	@chmod ${BINMODE} ${WRKDIR}/bin/{${_MPWRAP_CC},${_MPWRAP_CXX}}
	@${_MAKE_COOKIE} $@

${_EXTRACT_COOKIE}: ${_WRKDIR_COOKIE} ${_SYSTRACE_COOKIE}
.if ${DIST_SOURCE:L} == "distfile"
	@cd ${.CURDIR} && exec ${MAKE} NOSUPDISTFILES=1 \
	    checksum build-depends lib-depends
	@${ECHO_MSG} "===>  Extracting for ${FULLPKGNAME}${_MASTER}"
.  if target(pre-extract)
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} pre-extract
.  endif
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} do-extract
.else
	@cd ${.CURDIR} && exec ${MAKE} build-depends lib-depends
	@${ECHO_MSG} "===>  Copying source for ${FULLPKGNAME}${_MASTER}"
	@mkdir -p ${WRKSRC}
	cd ${WRKSRC} && lndir ${DIST_SOURCEDIR}
.endif
	@-cd ${WRKDIST} && chmod -R u+w .
.if target(post-extract)
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} post-extract
.endif
	@${_MAKE_COOKIE} $@

.if !target(do-extract)
do-extract:
# What EXTRACT normally does:
	@PATH=${PORTPATH}; set -e; cd ${WRKDIR}; \
	for archive in ${EXTRACT_ONLY}; do \
		case $$archive in \
		${EXTRACT_CASES} \
		esac; \
	done
# End of EXTRACT
.endif


# Both distpatch and patch invoke pre-patch, if it's defined.
# Hence it needs special treatment (a specific cookie).
.if target(pre-patch)
${_PREPATCH_COOKIE}:
	@cd ${.CURDIR} && exec ${MAKE} pre-patch
.  if ${PATCH_CHECK_ONLY:L} != "yes"
	@${_MAKE_COOKIE} $@
.  endif
.endif



# The real distpatch

${_DISTPATCH_COOKIE}: ${_EXTRACT_COOKIE}
.if target(pre-patch)
	@cd ${.CURDIR} && exec ${MAKE} ${_PREPATCH_COOKIE}
.endif
.if target(do-distpatch)
	@cd ${.CURDIR} && exec ${MAKE} do-distpatch
.else
# What DISTPATCH normally does
.  if defined(_PATCHFILES)
	@${ECHO_MSG} "===>  Applying distribution patches for ${FULLPKGNAME}${_MASTER}"
	@cd ${FULLDISTDIR}; \
	  for patchfile in ${_PATCHFILES}; do \
	  	case ${PATCH_DEBUG:L:Q} in \
		no)	;; \
		*)	${ECHO_MSG} "===>   Applying distribution patch $$patchfile" ;; \
		esac; \
		case $$patchfile in \
			${PATCH_CASES} \
		esac; \
	  done
.  endif
# End of DISTPATCH.
.endif
.if target(post-distpatch)
	@cd ${.CURDIR} && exec ${MAKE} post-distpatch
.endif
.if ${PATCH_CHECK_ONLY:L} != "yes"
	@${_MAKE_COOKIE} $@
.endif

# The real patch

${_PATCH_COOKIE}: ${_EXTRACT_COOKIE}
	@${ECHO_MSG} "===>  Patching for ${FULLPKGNAME}${_MASTER}"
.if target(pre-patch)
	@cd ${.CURDIR} && exec ${MAKE} ${_PREPATCH_COOKIE}
.endif
.if target(do-patch)
	@cd ${.CURDIR} && exec ${MAKE} do-patch
.else
# What PATCH normally does:
# XXX test for efficiency, don't bother with distpatch if it's not needed
.  if target(do-distpatch) || target(post-distpatch) || defined(PATCHFILES)
	@cd ${.CURDIR} && exec ${MAKE} distpatch
.  endif
	@if cd ${PATCHDIR} 2>/dev/null || [ x"${PATCH_LIST:M/*}" != x"" ]; then \
		error=false; \
		for i in ${PATCH_LIST}; do \
			case $$i in \
			*.orig|*.rej|*~) \
				${ECHO_MSG} "===>   Ignoring patchfile $$i" ; \
				;; \
			*) \
			    if [ -e $$i ]; then \
					case ${PATCH_DEBUG:L:Q} in \
					no)	;; \
					*)	${ECHO_MSG} "===>   Applying ${OPSYS} patch $$i" ;; \
					esac; \
					${PATCH} ${PATCH_ARGS} <$$i || \
						{ echo "***>   $$i did not apply cleanly"; \
						error=true; }\
				else \
					if [ $$i != "patch-*" ]; then \
						echo "===>   Can't find patch matching $$i"; \
						error=true; \
					fi; \
				fi; \
				;; \
			esac; \
		done;\
		if $$error; then exit 1; fi; \
	fi
# End of PATCH.
.endif
.if target(post-patch)
	@cd ${.CURDIR} && exec ${MAKE} post-patch
.endif
.for _m in ${MODULES}
.  if defined(MOD${_m:U}_post-patch)
	@${MOD${_m:U}_post-patch}
.  endif
.endfor
.if !empty(REORDER_DEPENDENCIES) && ${PATCH_CHECK_ONLY:L} != "yes"
	sed -e '/^#/d' ${REORDER_DEPENDENCIES} | \
	  tsort -r|while read f; do \
	    cd ${WRKSRC}; \
		case $$f in \
		/*) \
			find . -name $${f#/} -print | while read i; \
				do echo "Touching $$i"; touch $$i; done \
			;; \
		*) \
			if test -e $$f ; then \
				echo "Touching $$f"; touch $$f; \
			fi \
			;; \
		esac; done
.endif
.if ${PATCH_CHECK_ONLY:L} != "yes"
	@${_MAKE_COOKIE} $@
.endif

# The real configure

${_CONFIGURE_COOKIE}: ${_PATCH_COOKIE}
	@${ECHO_MSG} "===>  Configuring for ${FULLPKGNAME}${_MASTER}"
	@mkdir -p ${WRKBUILD} ${WRKPKG}
.if target(pre-configure)
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} pre-configure
.endif
.if ${USE_SCHILY:L} != "no"
.  if (${OStype} == "MidnightBSD") || (${OStype} == "MirBSD")
	sed -e 's/@@OScompat@@/${OScompat}/' \
	    -e 's/@@OStype@@/${OStype}/' \
	    -e 's#!/bin/mksh#!'${MKSH:Q}'' \
	    <${PORTSDIR}/infrastructure/db/uname.sed >${WRKDIR}/bin/uname
	chmod ${BINMODE} ${WRKDIR}/bin/uname
.  endif
	ln -sf ${WRKDIR}/bin/${_MPWRAP_CC} ${WRKDIR}/bin/cc
.  if ${MACHINE} != "i386"
	ln -sf ${WRKSRC}/RULES/i386-openbsd-cc.rul \
	    ${WRKSRC:Q}/RULES/${MACHINE:Q}-openbsd-cc.rul
.  endif
.  if ${OStype} == "Darwin"
	ln -sf ${WRKSRC:Q}/RULES/power-macintosh-darwin-cc.rul \
	    ${WRKSRC:Q}/RULES/i386-darwin-cc.rul
.  endif
.endif
.if target(do-configure)
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} do-configure
.elif ${CONFIGURE_STYLE:L} != "no"
# What CONFIGURE normally does
	@if [ -f ${SCRIPTDIR}/configure ]; then \
		cd ${.CURDIR} &&  ${_SYSTRACE_CMD} ${SETENV} \
		    ${SCRIPTS_ENV} ${SH} ${SCRIPTDIR}/configure; \
	fi
.  for _c in ${CONFIGURE_STYLE:L}
.    if defined(MOD${_c:U}_configure)
	@${MOD${_c:U}_configure}
.    endif
.  endfor
# End of CONFIGURE.
.endif
.if target(post-configure)
	@cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} post-configure
.endif
	@${_MAKE_COOKIE} $@

# The real build

${_BUILD_COOKIE}: ${_CONFIGURE_COOKIE}
.if ${NO_BUILD:L} == "no"
	@${ECHO_MSG} "===>  Building for ${FULLPKGNAME}${_MASTER}"
.  if ${VMEM_WARNING:L} == "yes"
	@echo ""; \
	echo "*** WARNING: you may see an error such as"; \
	echo "***       virtual memory exhausted"; \
	echo "*** when building this package.  If you do you must increase"; \
	echo "*** your limits.  See the man page for your shell and look"; \
	echo "*** for the 'limit' or 'ulimit' command. You may also want to"; \
	echo "*** see the login.conf(5) manual page."; \
	echo "*** Some examples are: "; \
	echo "*** 	csh(1) and tcsh(1): limit datasize <KiB memory>"; \
	echo "***	ksh(1), zsh(1) and bash(1): ulimit -d <KiB memory>"; \
	echo ""
.  endif
.  if target(pre-build)
	@${_VMEM_UNLOCK} \
	cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} pre-build
.  endif
.  for _c in ${CONFIGURE_STYLE:L}
.    if defined(MOD${_c:U}_pre_build)
	@${_VMEM_UNLOCK} \
	${MOD${_c:U}_pre_build}
.    endif
.  endfor
.  if target(do-build)
	@${_VMEM_UNLOCK} \
	cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} do-build
.  else
# What BUILD normally does:
	@${_VMEM_UNLOCK} \
	cd ${WRKBUILD} && exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE:Q} ${ALL_TARGET}
# End of BUILD
.  endif
.  if target(post-build)
	@${_VMEM_UNLOCK} \
	cd ${.CURDIR} && exec ${_SYSTRACE_CMD} ${MAKE} post-build
.  endif
.endif
	@${_MAKE_COOKIE} $@

${_REGRESS_COOKIE}: ${_BUILD_COOKIE}
.if ${NO_REGRESS:L} == "no"
	@${ECHO_MSG} "===>  Regression check for ${FULLPKGNAME}${_MASTER}"
.  if target(pre-regress)
	@cd ${.CURDIR} && exec ${MAKE} pre-regress
.  endif
.  if target(do-regress)
	@cd ${.CURDIR} && exec ${MAKE} do-regress
.  else
# What REGRESS normally does:
	@cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} ${REGRESS_ENV} \
	    ${MAKE_PROGRAM} ${REGRESS_FLAGS} -f ${MAKE_FILE:Q} ${REGRESS_TARGET}
# End of REGRESS
.  endif
.  if target(post-regress)
	@cd ${.CURDIR} && exec ${MAKE} post-regress
.  endif
.else
	@echo 1>&2 "No regression check for ${FULLPKGNAME}"
.endif
	@${_MAKE_COOKIE} $@

.if ${FAKE:L} == "yes"
${_FAKE_COOKIE}: ${_BUILD_COOKIE} ${WRKPKG}/mtree.spec
	@${ECHO_MSG} "===>  Faking installation for ${FULLPKGNAME}${_MASTER}"
	@if [ x$$(${SUDO} ${SH} -c umask) != x${DEF_UMASK} ]; then \
		echo >&2 "Error: your umask is \"$$(${SH} -c umask)"\".; \
		exit 1; \
	fi
	@${SUDO} rm -rf ${WRKINST}
	@${SUDO} ${INSTALL_PROGRAM_DIR} ${WRKINST}
	@${SUDO} /usr/sbin/mtree -U -e -d -n -p ${WRKINST} \
		-f ${WRKPKG}/mtree.spec  >/dev/null
.  if ${PREFIX} == "/usr"
	@${SUDO} ln -s ../man ${WRKINST}/usr/share/man
.  endif
.  for _p in ${PROTECT_MOUNT_POINTS}
	@${SUDO} mount -u -r ${_p}
.  endfor
.  for _m in ${MODULES}
.    if defined(MOD${_m:U}_pre-fake)
	@${MOD${_m:U}_pre-fake}
.    endif
.  endfor

.  if target(pre-fake)
	@cd ${.CURDIR} && exec ${SUDO} ${_SYSTRACE_CMD} \
	    ${MAKE} pre-fake ${_FAKE_SETUP}
.  endif
	@${SUDO} ${_MAKE_COOKIE} ${_INSTALL_PRE_COOKIE}
.  if target(pre-install)
	@cd ${.CURDIR} && exec ${SUDO} ${_SYSTRACE_CMD} \
	    ${MAKE} pre-install ${_FAKE_SETUP}
.  endif
.  if target(do-install)
	@cd ${.CURDIR} && exec ${SUDO} ${_SYSTRACE_CMD} \
	    ${MAKE} do-install ${_FAKE_SETUP}
.  else
# What FAKE normally does:
	@cd ${WRKBUILD} && exec ${SUDO} ${_SYSTRACE_CMD} \
	    ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} \
	    ${MAKE_PROGRAM} ${FAKE_FLAGS} -f ${MAKE_FILE:Q} ${FAKE_TARGET}
# End of FAKE.
.  endif
.  for _m in ${MODULES}
.    if defined(MOD${_m:U}_post-fake)
	@${MOD${_m:U}_post-fake}
.    endif
.  endfor
.  if target(post-install)
	@cd ${.CURDIR} && exec ${SUDO} ${_SYSTRACE_CMD} \
	    env FLAVOUR=${FLAVOUR:Q} \
	    ${MAKE} post-install ${_FAKE_SETUP}
.  endif
.  for _p in ${PROTECT_MOUNT_POINTS}
	@${SUDO} mount -u -w ${_p}
.  endfor
.  if ${PREFIX} == "/usr"
	@cd ${WRKINST:Q}/usr/share; \
	    [[ ! -h man || $$(readlink man) != ../man ]] || ${SUDO} rm man
.  endif
	@${SUDO} ${_MAKE_COOKIE} $@

# The real install

${_INSTALL_COOKIE}:  ${_PACKAGE_COOKIES}
	@cd ${.CURDIR} && DEPENDS_TARGET=install \
	    exec ${MAKE} run-depends lib-depends
	@cd ${.CURDIR} && exec ${MAKE} install-binpkg
	@-${SUDO} ${_MAKE_COOKIE} $@

install-binpkg:
	@${ECHO_MSG} "===>  Installing ${FULLPKGNAME${SUBPACKAGE}} from ${PKGFILE${SUBPACKAGE}}"
.  for _m in ${MODULES}
.    if defined(MOD${_m:U}_pre_install)
	@${MOD${_m:U}_pre_install}
.    endif
.  endfor
.  if ${TRUST_PACKAGES:L} == "yes"
	@if ${PKG_CMD_INFO} -qe \
	    ${FULLPKGNAME${SUBPACKAGE}}; then \
		echo "Package ${FULLPKGNAME${SUBPACKAGE}} is already installed"; \
	else \
		${SUDO} ${SETENV} PKG_PATH=${PKGREPOSITORY}:${PKG_PATH} \
		    PKG_TMPDIR=${PKG_TMPDIR} PATH=${PKG_CMDDIR:Q}:$$PATH \
		    ${PKG_CMD_ADD} ${PKGFILE${SUBPACKAGE}}; \
	fi
.  else
	@${SUDO} ${SETENV} PKG_PATH=${PKGREPOSITORY}:${PKG_PATH} \
	    PKG_TMPDIR=${PKG_TMPDIR} PATH=${PKG_CMDDIR:Q}:$$PATH \
	    ${PKG_CMD_ADD} ${PKGFILE${SUBPACKAGE}}
.  endif
.endif

# The real package

_package: ${_PKG_PREREQ}
	@[[ -d ${PKGREPOSITORY} ]] || mkdir -p ${PKGREPOSITORY}
	@if [[ ! -w ${PKGREPOSITORY} ]]; then \
		print -u2 'Error: ${PKGREPOSITORY} is not writable for you!'; \
		exit 1; \
	fi
.if target(pre-package)
	@cd ${.CURDIR} && exec ${MAKE} pre-package
.endif
.if target(do-package)
	@cd ${.CURDIR} && exec ${MAKE} do-package
.else
# What PACKAGE normally does:
	@${ECHO_MSG} "===>  Building package for ${FULLPKGNAME${SUBPACKAGE}}"
# PLIST should normally hold no duplicates.
# This is left as a warning, because stuff such as @exec %F/%D
# completion may cause legitimate dups.
	@duplicates=$$(sort <${WRKPKG}/PLIST${SUBPACKAGE} \
	    | egrep -v '@(comment|mode|owner|group)' | uniq -d); \
	case "$${duplicates}" in "");; \
	*)	echo "\n*** WARNING *** Duplicates in PLIST:\n$$duplicates\n";; \
	esac
	@${_VMEM_UNLOCK_CMDS} \
	cd ${.CURDIR} && if ${SUDO} ${SETENV} PATH=${PKG_CMDDIR:Q}:$$PATH \
	    ${PKG_CMD_CREATE} ${PKG_ARGS} ${PKGFILE${SUBPACKAGE}}; then \
		mode=$$(id -u):$$(id -g); \
		${SUDO} ${CHOWN} $${mode} ${PKGFILE${SUBPACKAGE}}; \
		${MAKE} _package-links; \
	  else \
		${SUDO} ${MAKE} CLEANDEPENDS=No clean=package; \
		exit 1; \
	  fi
# End of PACKAGE.
.endif
.if target(post-package)
	@cd ${.CURDIR} && exec ${MAKE} post-package
.endif

fetch-all:
	@cd ${.CURDIR} && exec ${MAKE} __FETCH_ALL=Yes __ARCH_OK=Yes \
	    NO_IGNORE=Yes fetch

# Separate target for each file fetch will retrieve
# In the first loop, go over all CVS distfiles.
# In the second loop, go over ALLFILES, but ignore
# these for which there is already a target.

.if ${MCZ_FETCH:L} == "no"
.  for _i in - 0 1 2 3 4 5 6 7 8 9
.    if defined(_CVS_FETCH${_i:N-}) && ${REFETCH} != "true"
${FULLDISTDIR}/${_CVS_DISTF${_i:N-}}:
	@if [[ ! -w ${FULLDISTDIR} ]]; then \
		print -u2 'Error: some subdirectory of ${DISTDIR}' \
		    'is not writable for you!'; \
		exit 1; \
	fi
	@[[ -e ${FULLDISTDIR}/${_CVS_DISTF${_i:N-}} ]] || { \
		cd ${.CURDIR}; ${MAKE} fetch-depends; \
		PATH=${_PORTPATH:Q} TMPDIR=${TMPDIR:Q} \
		    ${_CVS_FETCH${_i:N-}}; \
		file=${@:S@^${DISTDIR}/@@}; \
		ck=$$(cd ${DISTDIR} && ${_size_fragment}); \
		if [[ ! -s ${CHECKSUM_FILE} ]]; then \
			${ECHO_MSG} ">> No checksum file for ${FULLDISTDIR}/${_CVS_DISTF${_i:N-}}"; \
		elif grep -qe "^$$ck\$$" \
		    -e "^Size$${ck#SIZE} bytes\$$" \
		    ${CHECKSUM_FILE}; then \
			${ECHO_MSG} ">> Size matches for ${FULLDISTDIR}/${_CVS_DISTF${_i:N-}}"; \
		elif grep -qe "SIZE ($$file)" -e "Size ($$file)" ${CHECKSUM_FILE}; then \
			${ECHO_MSG} ">> Size does not match for ${FULLDISTDIR}/${_CVS_DISTF${_i:N-}}"; \
			${ECHO_MSG} ">> Try to refetch with mmake fetch REFETCH=true"; \
			false; \
		else \
			${ECHO_MSG} ">> No size recorded for ${FULLDISTDIR}/${_CVS_DISTF${_i:N-}}"; \
		fi; \
	}
.    endif
.  endfor
.endif
.for _F in ${ALLFILES:S@^@${FULLDISTDIR}/@}
.  if !target(${_F})
${_F}:
.    if ${FETCH_MANUALLY:L} != "no"
.      for _M in ${FETCH_MANUALLY}
	@echo "*** "${_M}
.      endfor
	@exit 1
.    else
	@mkdir -p ${_F:H}
	@if [[ ! -w ${_F:H} ]]; then \
		print -u2 'Error: some subdirectory of ${DISTDIR}' \
		    'is not writable for you!'; \
		exit 1; \
	fi
	@cd ${_F:H}; \
	select=${_EVERYTHING:M*${_F:S@^${FULLDISTDIR}/@@}\:[0-9]}; \
	f=${_F:S@^${FULLDISTDIR}/@@}; \
	${ECHO_MSG} ">> $$f doesn't seem to exist on this system."; \
	${_CDROM_OVERRIDE}; \
	${_SITE_SELECTOR}; \
	for site in $$sites; do \
		${ECHO_MSG} ">> Attempting to fetch ${_F} from $${site}."; \
		if ${FETCH_CMD} ${_F} $${site}$$f; then \
			file=${_F:S@^${DISTDIR}/@@}; \
			ck=$$(cd ${DISTDIR} && ${_size_fragment}); \
			if grep -qe "^$$ck\$$" \
			    -e "^Size$${ck#SIZE} bytes\$$" \
			    ${CHECKSUM_FILE}; then \
				${ECHO_MSG} ">> Size matches for ${_F}"; \
				exit 0; \
			elif grep -qe "SIZE ($$file)" -e "Size ($$file)" ${CHECKSUM_FILE}; then \
				${ECHO_MSG} ">> Size does not match for ${_F}"; \
			else \
				${ECHO_MSG} ">> No size recorded for ${_F}"; \
				exit 0; \
			fi; \
		fi; \
	done; exit 1
.    endif
.  endif
.endfor

# Some support rules for do-package

_package-links:
	@cd ${.CURDIR} && exec ${MAKE} _delete-package-links
.for _l in FTP CDROM
.  if ${PERMIT_PACKAGE_${_l}:L} == "yes"
	@echo "Link to ${${_l}_PACKAGES}/${FULLPKGNAME${SUBPACKAGE}}${PKG_SUFX}"
	@mkdir -p -m 0775 ${${_l}_PACKAGES}
	@rm -f ${${_l}_PACKAGES}/${FULLPKGNAME${SUBPACKAGE}}${PKG_SUFX}
	@ln ${PKGFILE${SUBPACKAGE}} \
	  ${${_l}_PACKAGES}/${FULLPKGNAME${SUBPACKAGE}}${PKG_SUFX} 2>/dev/null || \
	  cp -p ${PKGFILE${SUBPACKAGE}} \
	  ${${_l}_PACKAGES}/${FULLPKGNAME${SUBPACKAGE}}${PKG_SUFX}
.  endif
.endfor

_delete-package-links:
.for _l in FTP CDROM
	@rm -f ${${_l}_PACKAGES}/${FULLPKGNAME${SUBPACKAGE}}${PKG_SUFX}
.endfor

# Cleaning up

clean:
.if ${_clean:L:Mdepends} && ${_CLEANDEPENDS:L} == "yes"
	@${MAKE} all-dir-depends | tsort -rq | sed '$$d' | \
	    while read dir; do \
		unset FLAVOUR SUBPACKAGE || true; \
		${_flavour_fragment}; \
		eval $$toset ${MAKE} _CLEANDEPENDS=No clean; \
	done
.endif
	@${ECHO_MSG} "===>  Cleaning for ${FULLPKGNAME${SUBPACKAGE}}"
.  if ${_clean:L:Mfake}
	@if cd ${WRKINST} 2>/dev/null; then ${SUDO} rm -rf ${WRKINST}; fi
.  endif
.  if ${_clean:L:Mwork}
.    if ${_clean:L:Mflavours}
	@for i in ${.CURDIR}/w-*; do \
		if [ -L $$i ]; then ${SUDO} rm -rf $$(readlink $$i); fi; \
		${SUDO} rm -rf $$i; \
	done
.    else
	@[ ! -L ${WRKDIR} ] || ${SUDO} rm -rf $$(readlink ${WRKDIR})
	@${SUDO} rm -rf ${WRKDIR}
.    endif
.  endif
.  if ${_clean:L:Mdist}
	@${ECHO_MSG} "===>  Dist cleaning for ${FULLPKGNAME${SUBPACKAGE}}"
	@if cd ${FULLDISTDIR} 2>/dev/null; then \
		if [ "${_DISTFILES}" -o "${_PATCHFILES}" ]; then \
			rm -f ${_DISTFILES} ${_PATCHFILES}; \
		fi \
	fi
	@if cd ${DISTDIR}/CDROM/${DIST_SUBDIR} 2>/dev/null; then \
		if [ "${_DISTFILES}" -o "${_PATCHFILES}" ]; then \
			rm -f ${_DISTFILES} ${_PATCHFILES}; \
		fi \
	fi
	@if cd ${DISTDIR}/FTP/${DIST_SUBDIR} 2>/dev/null; then \
		if [ "${_DISTFILES}" -o "${_PATCHFILES}" ]; then \
			rm -f ${_DISTFILES} ${_PATCHFILES}; \
		fi \
	fi
.    if !empty(DIST_SUBDIR)
	-@rmdir ${FULLDISTDIR}
.    endif
.  endif
.  if ${_clean:L:Minstall}
.    if ${_clean:L:Msub}
.      for _s in ${MULTI_PACKAGES}
	-${SUDO} ${SETENV} PATH=${PKG_CMDDIR:Q}:$$PATH \
	    ${PKG_CMD_DELETE} ${FULLPKGNAME${_s}}
.      endfor
.    else
	-${SUDO} ${SETENV} PATH=${PKG_CMDDIR:Q}:$$PATH \
	    ${PKG_CMD_DELETE} ${FULLPKGNAME${SUBPACKAGE}}
.    endif
.  endif
.  if ${_clean:L:Mpackages} || ${_clean:L:Mpackage} && ${_clean:L:Msub}
	rm -f ${_PACKAGE_COOKIES}
.    if defined(MULTI_PACKAGES)
.      for _s in ${MULTI_PACKAGES}
	@cd ${.CURDIR} && SUBPACKAGE=${_s:Q} exec ${MAKE} _delete-package-links
.      endfor
.    endif
.  elif ${_clean:L:Mpackage}
	@cd ${.CURDIR} && exec ${MAKE} _delete-package-links
	rm -f ${PKGFILE${SUBPACKAGE}}
.  endif
.  if ${_clean:L:Mreadmes}
	rm -f ${.CURDIR}/${FULLPKGNAME}.html
.      for _s in ${MULTI_PACKAGES}
	rm -f ${.CURDIR}/${FULLPKGNAME${_s}}.html
.      endfor
.  endif
.  if ${_clean:L:Mbulk}
	rm -f ${_BULK_COOKIE}
.  endif

# packing list utilities.  This generates a packing list from a recently
# installed port.  Not perfect, but pretty close.  The generated file
# will have to have some tweaks done by hand.
# Note: add @comment PACKAGE(arch=${MACHINE_ARCH},
#		opsys=${OPSYS}, vers=${OPSYS_VER})
# when port is installed or package created.
#
.if ${FAKE:L} == "yes"
_tmpvars:=
.  for _v in ${SUBST_VARS:NHOMEPAGE:NSYSCONFDIR:NRESPONSIBLE}
_tmpvars+=		${_v}=${${_v}:Q}
.  endfor

plist update-plist: fake
	@mkdir -p ${PKGDIR}
	@DESTDIR=${WRKINST} PREFIX=${WRKINST}${PREFIX} LDCONFIG=${LDCONFIG:Q} \
	LOCALBASE=${PREFIX} \
	MTREE_FILE=${WRKPKG}/mtree.spec \
	INSTALL_PRE_COOKIE=${_INSTALL_PRE_COOKIE} \
	PKGREPOSITORY=${PKGREPOSITORY} \
	PLIST=${PLIST} \
	PFRAG=${PKGDIR}/PFRAG \
	FLAVOURS=${FLAVOURS:Q} MULTI_PACKAGES=${MULTI_PACKAGES:Q} \
	OKAY_FILES=${_FAKE_COOKIE:Q}\ ${_INSTALL_PRE_COOKIE:Q} \
	perl ${PORTSDIR}/infrastructure/scripts/make-plist ${PKGDIR} ${_tmpvars}
.endif

update-patches:
	@toedit=$$(WRKDIST=${WRKDIST} PATCHDIR=${PATCHDIR} \
	    PATCH_LIST=${PATCH_LIST:Q} DIFF_ARGS=${DIFF_ARGS:Q} \
	    DISTORIG=${DISTORIG} PATCHORIG=${PATCHORIG} ${_GDIFFLAG} \
	    ${SHELL} ${PORTSDIR}/infrastructure/scripts/update-patches); \
	case $$toedit in "");; \
	*) read i?'edit patches: '; \
	cd ${PATCHDIR} && $${VISUAL:-$${EDITOR:-/usr/bin/vi}} $$toedit;; esac


# mirroring utilities
fetch-makefile:
	@echo -n "all"
.if ${PERMIT_DISTFILES_FTP:L} == "yes"
	@echo -n " ftp"
.endif
.if ${PERMIT_DISTFILES_CDROM:L} == "yes"
	@echo -n " cdrom"
.endif
	@echo ":: ${_FMN}"
# write generic package dependencies
	@echo ".PHONY: ${_FMN}"
.if ${RECURSIVE_FETCH_LIST:L} == "yes"
	@echo "${_FMN}: ${_ALLFILES} "$$(_FULL_PACKAGE_NAME=Yes \
	    ${MAKE} full-all-depends)
.else
	@echo "${_FMN}: ${_ALLFILES}"
.endif
	@exec ${MAKE} __FETCH_ALL=Yes __ARCH_OK=Yes \
	    NO_IGNORE=Yes _fetch-makefile

_fetch-makefile:
.if !empty(ALLFILES)
.  for _F in ${_ALLFILES}
	@if ! fgrep -q "|${_F}|" $${_DONE_FILES}; then \
		echo "|${_F}|" >>$${_DONE_FILES}; \
		${MAKE} _fetch-onefile _file=${_F}; \
	fi
.  endfor
.endif
	@echo


_fetch-onefile:
# XXX loop so that M${_F} will work
.for _F in ${_file}
	@echo '${_F}: $$F'
	@echo -n '\t@RESPONSIBLE="${RESPONSIBLE}" '
.  if !empty(DIST_SUBDIR)
	@echo -n 'DIST_SUBDIR="${DIST_SUBDIR}" '
.  endif
	@echo '\\'
	@select='${_EVERYTHING:M*${_F:S@^${DIST_SUBDIR}/@@}\:[0-9]}'; \
	${_SITE_SELECTOR}; \
	echo "\t SITES=\"$$sites\" \\"
.  if ${FETCH_MANUALLY:L} != "no"
	@echo '\t FETCH_MANUALLY="Yes" \\'
.  endif
.  if !defined(NO_CHECKSUM) && !empty(_CKSUMFILES:M${_F})
	@checksum_file=${CHECKSUM_FILE}; \
	if [ ! -f $$checksum_file ]; then \
	  echo >&2 "Missing checksum file: $$checksum_file"; \
	  echo '\t ERROR="no checksum file" \\'; \
	else \
	  for c in ${_CIPHERS}; do \
		if set -- $$(grep -i "^$$c (${_F})" $$checksum_file); then \
			break; fi; \
	  done; \
	  case "$$4" in \
		"") \
		  echo >&2 "No checksum recorded for ${_F}."; \
		  echo '\t ERROR="no checksum" \\';; \
		"IGNORE") \
		  echo >&2 "Checksum for ${_F} is IGNORE in $$checksum_file"; \
		  echo >&2 'but file is not in $${IGNORE_FILES}'; \
		  echo '\t ERROR="IGNORE inconsistent" \\';; \
		*) \
		  echo "\t CIPHER=\"$$c\" CKSUM=\"$$4\" \\";; \
	  esac; \
	fi
.  endif
	@echo '\t $${EXEC} $${FETCH} "$$@"'
.endfor

# foobar

.if (${MACHINE_OS} == "Darwin") || (${OStype} == "MidnightBSD")
.  if exists(${_ORIG_CC})
CC_SPECS=	${_ORIG_CC}
.  elif exists(/usr/bin/${_ORIG_CC})
CC_SPECS=	/usr/bin/${_ORIG_CC}
.  else
.    ifndef CC_SPECS
CC_SPECS!=	whence -p ${_ORIG_CC:Q} 2>&- || \
		whence -p $$(echo ${_ORIG_CC:Q} | sed 's/ .*//') 2>&-
.      if ${__MAKEFLAGS_HACKERY:L} == "yes"
.MAKEFLAGS:=	${.MAKEFLAGS} CC_SPECS=${CC_SPECS:Q}
.      endif
.    endif
.    if !exists(${CC_SPECS})
CC_SPECS:=
.    endif
.  endif

_patch_cc_specs=\
	if fgrep -q /usr/bin/libtool $$t; then \
		print ',g!/usr/bin/libtool!s!!'${LOCALBASE:Q}'/db/libtool!g\nwq' | \
		    ed -s $$t; \
	else \
		reallinker=$$(${_ORIG_CC} -print-prog-name=collect2); \
		[[ -x $$reallinker ]] || \
		    reallinker=$$(${_ORIG_CC} -print-prog-name=ld); \
		print '/^\*linker:$$/+1s!^collect2!${LOCALBASE}/db/collect2' \
		    "-Ww,collect2 $$reallinker!\nwq" | ed -s $$t; \
	fi
.if exists(${.SYSMK}/libmirmake.a)
_patch_cc_specs+=;\
	print '/^\*link_gcc_c_sequence:$$/+1s^-L'${.SYSMK:Q} \
	    '%{!shared:-lmirmake} \nwq' | ed -s $$t
.endif

${LOCALBASE}/db/specs.${_ORIG_CC:S!/!_!g}: ${CC_SPECS} \
    ${PORTSDIR}/infrastructure/mk/bsd.port.mk
	@if ! t=$$(mktemp /tmp/XXXXXXXXXXXX); then \
		print -u2 Error: cannot make temporary file; \
		exit 1; \
	fi; \
	${_ORIG_CC} -dumpspecs >$$t; \
	${_patch_cc_specs}; \
	if ! ${SUDO} ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} $$t $@; then \
		print -u2 Error: cannot install specs file; \
		rm -f $$t; \
		exit 1; \
	fi; \
	rm -f $$t; :
.endif

# This target generates an index entry suitable for aggregation into
# a large index.  Format is:
#
# distribution-name|port-path|installation-prefix|comment|homepage| \
#  description-file|maintainer|categories|lib-deps|build-deps|run-deps| \
#  fos-os|for-arch|package-cdrom|package-ftp|distfiles-cdrom|distfiles-ftp
_EXTRA_DESCRIBE=
.if defined(BROKEN)
_EXTRA_DESCRIBE+=	"(broken)"
.endif
.if ${USE_CXX:L} == "yes"
_EXTRA_DESCRIBE+=	"(uses C++)"
.endif
.if ${USE_MOTIF:L} != "no"
_EXTRA_DESCRIBE+=	"(uses Motif)"
.elif ${USE_X11:L} == "yes"
_EXTRA_DESCRIBE+=	"(uses X11)"
.endif
.if (${USE_GMAKE:L} == "yes") || (${USE_SCHILY:L} == "yes")
_EXTRA_DESCRIBE+=	"(uses GNU Make)"
.endif
.if ${USE_SCHILY:L} == "yes"
_EXTRA_DESCRIBE+=	"(uses Schily)"
# we don’t distribute such filth from hostile upstreams
PERMIT_PACKAGE_CDROM:=	No
PERMIT_PACKAGE_FTP:=	No
.endif
.if ${_USE_ZIP:L} == "yes"
_EXTRA_DESCRIBE+=	"(uses PKZip)"
.endif
.if ${_USE_BZIP2:L} == "yes"
_EXTRA_DESCRIBE+=	"(uses BZip2)"
.endif
.if ${NO_SYSTRACE:L} != "no"
_EXTRA_DESCRIBE+=	"(disables systrace)"
.endif
.for _i in ${EMUL}
_EXTRA_DESCRIBE+=	"(uses ${_i} personality)"
.endfor
.if ${_EXTRA_DESCRIBE} == ""
_EXTRA_DESCRIBE=
.endif
describe:
.if defined(MULTI_PACKAGES) && !defined(PACKAGING)
	@cd ${.CURDIR} && SUBPACKAGE=${SUBPACKAGE:Q} FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING=${SUBPACKAGE:Q} exec ${MAKE} describe
.  if empty(SUBPACKAGE)
.    for _sub in ${MULTI_PACKAGES}
	@cd ${.CURDIR} && SUBPACKAGE=${_sub:Q} FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING=${_sub:Q} exec ${MAKE} describe
.    endfor
.  endif
.else
	@echo -n "${FULLPKGNAME${SUBPACKAGE}}|${FULLPKGPATH}|"
.  if ${PREFIX} == ${LOCALBASE}
	@echo -n "|"
.  else
	@echo -n "${PREFIX}|"
.  endif
	@echo -n ${_COMMENT:Q}${_EXTRA_DESCRIBE}\|${HOMEPAGE:Q}\|; \
	if [ -f ${DESCR} ]; then \
		echo -n "${DESCR:S,^${PORTSDIR}/,,}|"; \
	else \
		echo -n "/dev/null|"; \
	fi; \
	echo -n "${RESPONSIBLE}|${CATEGORIES}|"
.  for _d in LIB BUILD RUN
.    if !empty(_${_d}_DEP2)
	@cd ${.CURDIR} && _FINAL_ECHO=: _INITIAL_ECHO=: exec \
	    ${MAKE} ${_d:L}-depends-list
.    endif
	@echo -n "|"
.  endfor
	@case "${ONLY_FOR_PLATFORM}!${NOT_FOR_PLATFORM}" in \
	"!")	echo -n "any|" ;; \
	*)	sp=; only="${ONLY_FOR_PLATFORM}"; not="${NOT_FOR_PLATFORM}"; \
		test -z "$$only" || for a in $$only; do \
			echo -n "$$sp$$a"; \
			sp=" "; \
		done; \
		test -z "$$not" || for a in $$not; do \
			echo -n "$$sp!$$a"; \
			sp=" "; \
		done; \
		echo -n "|" ;; \
	esac

.  if defined(_BAD_LICENCING)
	@echo "?|?|?|?"
.  else
.    if ${PERMIT_PACKAGE_CDROM:L} == "yes"
	@echo -n "y|"
.    else
	@echo -n "n|"
.    endif
.    if ${PERMIT_PACKAGE_FTP:L} == "yes"
	@echo -n "y|"
.    else
	@echo -n "n|"
.    endif
.    if ${PERMIT_DISTFILES_CDROM:L} == "yes"
	@echo -n "y|"
.    else
	@echo -n "n|"
.    endif
.    if ${PERMIT_DISTFILES_FTP:L} == "yes"
	@echo "y"
.    else
	@echo "n"
.    endif
.  endif
.endif

readmes:
.if defined(MULTI_PACKAGES) && !defined(PACKAGING)
	@cd ${.CURDIR} && SUBPACKAGE=${SUBPACKAGE:Q} FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING=${SUBPACKAGE:Q} exec ${MAKE} readmes
.  if empty(SUBPACKAGE)
.    for _sub in ${MULTI_PACKAGES}
	@cd ${.CURDIR} && SUBPACKAGE=${_sub:Q} FLAVOUR=${FLAVOUR:Q} \
	    PACKAGING=${_sub:Q} exec ${MAKE} readmes
.    endfor
.  endif
.else
	@rm -f ${FULLPKGNAME${SUBPACKAGE}}.html
	@cd ${.CURDIR} && exec ${MAKE} README_NAME=${README_NAME} \
	    ${FULLPKGNAME${SUBPACKAGE}}.html
.endif


${FULLPKGNAME${SUBPACKAGE}}.html:
	@echo ${_COMMENT:Q} | ${HTMLIFY} >$@.tmp-comment
	@echo ${FULLPKGNAME${SUBPACKAGE}} | ${HTMLIFY} >$@.tmp3
.if defined(HOMEPAGE)
	@echo 'See <a href="'${HOMEPAGE:Q}'">'${HOMEPAGE:Q}'</a> for details.' >$@.tmp4
.else
	@echo "" >$@.tmp4
.endif
.if defined(MULTI_PACKAGES)
.  if empty(SUBPACKAGE)
	@echo "<h2>Subpackages</h2>" >$@.tmp-subpackages
	@echo "<ul>" >>$@.tmp-subpackages

.    for _S in ${MULTI_PACKAGES}
	@name=$$(SUBPACKAGE=${_S} ${MAKE} _print-packagename \
	    _FULL_PACKAGE_NAME=No); \
	echo "<li><a href=\"$$name.html\">$$name</a>" >>$@.tmp-subpackages
.    endfor
	@echo "</ul>" >>$@.tmp-subpackages
.  else
	@name=$$(unset SUBPACKAGE; ${MAKE} _print-packagename \
	    _FULL_PACKAGE_NAME=No); \
	echo "<h2>Subpackage of <a href=\"$$name.html\">$$name</a></h2>" \
	    >$@.tmp-subpackages
.  endif
.else
	@>$@.tmp-subpackages
.endif
.for _I in build run
.  if !empty(_ALWAYS_DEP) || !empty(_${_I:U}_DEP)
	@cd ${.CURDIR} && ${MAKE} full-${_I}-depends _FULL_PACKAGE_NAME=Yes \
	    | while read n; do \
		j=$$(dirname $$n|${HTMLIFY}); k=$$(basename $$n|${HTMLIFY}); \
		echo "<li><a href=\"${PKGDEPTH}$$j/$$k.html\">$$k</a>"; \
	    done  >$@.tmp-${_I}
.  else
	@echo "<li>none" >$@.tmp-${_I}
.  endif
.endfor
	@cat ${README_NAME} | sed \
	    -e 's|%%PORT%%|'"$$(echo ${FULLPKGPATH}  | ${HTMLIFY})"'|g' \
	    -e '/%%PKG%%/r$@.tmp3' -e '//d' \
	    -e '/%%COMMENT%%/r$@.tmp-comment' -e '//d' \
	    -e '/%%DESCR%%/r${PKGDIR}/DESCR${SUBPACKAGE}' -e '//d' \
	    -e '/%%HOMEPAGE%%/r$@.tmp4' -e '//d' \
	    -e '/%%BUILD_DEPENDS%%/r$@.tmp-build' -e '//d' \
	    -e '/%%RUN_DEPENDS%%/r$@.tmp-run' -e '//d' \
 	    -e '/%%SUBPACKAGES%%/r$@.tmp-subpackages' -e '//d' \
	    >>$@
	@rm -f $@.tmp*


print-build-depends:
.if !empty(_ALWAYS_DEP) || !empty(_BUILD_DEP)
	@echo -n 'This port requires package(s) "'
	@${MAKE} full-build-depends|tr '\012' '\040'|sed -e 's, $$,,'
	@echo '" to build.'
.endif

print-run-depends:
.if !empty(_ALWAYS_DEP) || !empty(_RUN_DEP)
	@echo -n 'This port requires package(s) "'
	@${MAKE} full-run-depends|tr '\012' '\040'|sed -e 's, $$,,'
	@echo '" to run.'
.endif

print-all-depends:
.if !empty(_ALWAYS_DEP) || !empty(_RUN_DEP) || !empty(_BUILD_DEP)
	@echo -n 'This port requires package(s) "'
	@${MAKE} full-all-depends|tr '\012' '\040'|sed -e 's, $$,,'
	@echo '" to run.'
.endif

print-depends: print-build-depends print-run-depends

.for _i in build all run
full-${_i}-depends:
	@${MAKE} ${_i}-dir-depends | tsort -rq | sed -e '$$d' \
	    | while read dir; do \
		unset FLAVOUR SUBPACKAGE || true; \
		${_flavour_fragment}; \
		eval $$toset ${MAKE} _print-packagename ; \
	done

for-${_i}-depends:
	@${MAKE} ${_i}-dir-depends | tsort -rq | sed -e '$$d' \
	    | while read dir; do \
		unset FLAVOUR SUBPACKAGE || true; \
		${_flavour_fragment}; \
		eval $$toset ${for-${_i}-depends}; \
	done
.endfor

relevant-checks:
.if ${PERMIT_PACKAGE_CDROM:L} == "yes" || ${PERMIT_PACKAGE_FTP:L} == "yes" \
    || ${USE_CXX:L} == "yes" || ${USE_X11:L} == "yes"
	@${MAKE} all-dir-depends | tsort -rq | sed -e '$$d' \
	    | while read dir; do \
		unset FLAVOUR SUBPACKAGE || true; \
		${_flavour_fragment}; \
		export _MASTER_PERMIT_CDROM=${PERMIT_PACKAGE_CDROM:Q} \
		    _MASTER_PERMIT_FTP=${PERMIT_PACKAGE_FTP:Q} \
		    _MASTER_BROKEN=${BROKEN:Q} \
		    _MASTER_IGNORE=${IGNORE:Q} \
		    _MASTER_USE_CXX=${USE_CXX:Q} \
		    _MASTER_USE_X11=${USE_X11:Q}; \
		eval $$toset ${MAKE} _relevant-checks; \
	done
.endif

_relevant-checks:
.if defined(_MASTER_BROKEN) && empty(_MASTER_BROKEN) \
    && defined(BROKEN) && !empty(BROKEN)
	@print -u2 "Warning: dependency ${PKGPATH} is marked BROKEN: ${BROKEN}"
.endif
.if defined(_MASTER_IGNORE) && empty(_MASTER_IGNORE) \
    && defined(IGNORE) && !empty(IGNORE) && empty(BROKEN)
	@print -u2 "Warning: dependency ${PKGPATH} is marked IGNORE:" ${IGNORE}
.endif
.for _i in FTP CDROM
.  if defined(_MASTER_PERMIT_${_i}) \
    && ${_MASTER_PERMIT_${_i}:L} == "yes" && ${PERMIT_PACKAGE_${_i}:L} != "yes"
	@echo >&2 "Warning: dependency ${PKGPATH} is not allowed for ${_i}"
.  endif
.endfor
.for _i in CXX X11
.  if defined(_MASTER_USE_${_i}) \
    && ${_MASTER_USE_${_i}:L} != "yes" && ${USE_${_i}:L} == "yes" \
    && !${FLAVOURS:U:MNO_${_i}}
	@echo >&2 "Warning: dependency ${PKGPATH} uses ${_i}"
.  endif
.endfor

.for _i in RUN BUILD LIB
${_i:L}-depends-list:
.  if !empty(_${_i}_DEP2)
	@unset FLAVOUR SUBPACKAGE || true; \
	: $${_INITIAL_ECHO:='echo -n "This port requires \""'}; \
	: $${_ECHO='echo -n'}; \
	: $${_FINAL_ECHO:='echo "\" for ${_i:L}."'}; space=; \
	eval $${_INITIAL_ECHO}; \
	for spec in $$(echo ${_${_i}_DEP2:Q} \
		| tr '\040' '\012' | sort -u); do \
		$${_ECHO} "$$space$${spec}"; \
		space=' '; \
	done; eval $${_FINAL_ECHO}
.  endif
.endfor

# recursive depend targets

# Print list of all libraries that we may depend upon.
_recurse-lib-depends-check:
.for _i in ${LIB_DEPENDS}
	@unset FLAVOUR SUBPACKAGE  || true; \
	echo ${_i:Q} | { \
		IFS=:; read dep pkg dir target; \
		IFS=,; for j in $$dep; do echo $$j; done; \
		if ! fgrep -q "|$$dir|" $${_DEPENDS_FILE}; then \
			echo "|$$dir|" >>$${_DEPENDS_FILE}; \
			${_flavour_fragment}; \
			eval $$toset ${MAKE} _recurse-lib-depends-check; \
		fi; \
	}
.endfor
.for _i in ${RUN_DEPENDS}
	@unset FLAVOUR SUBPACKAGE  || true; \
	echo ${_i:Q} | { \
		IFS=:; read dep pkg dir target; \
		if ! fgrep -q "|$$dir|" $${_DEPENDS_FILE}; then \
			echo "|$$dir|" >>$${_DEPENDS_FILE}; \
			${_flavour_fragment}; \
			eval $$toset ${MAKE} _recurse-lib-depends-check; \
		fi; \
	}
.endfor


# Write a correct list of dependencies for packages.
_recurse-solve-package-depends:
.for _i in ${RUN_DEPENDS}
	@unset FLAVOUR SUBPACKAGE || true; \
	echo ${_i:Q} |{ \
		IFS=:; read dep pkg dir target; \
		if [[ -n $$dir ]]; then \
			${_flavour_fragment}; \
			default=$$(eval $$toset ${MAKE} _print-packagename); \
		else \
			default=nonexistent; \
		fi; \
		: $${pkg:=$$default}; \
		echo "@newdepend $$self:$$pkg:$$default" >>$${_depends_result}; \
		if fgrep -q "|$$default|" $${_DEPENDS_FILE}; then \
			: ; \
		elif [[ -n $$dir ]]; then \
			echo "|$$default|" >>$${_DEPENDS_FILE}; \
			toset="$$toset self=\"$$default\""; \
			if ! eval $$toset ${MAKE} \
			    _recurse-solve-package-depends; then  \
				echo 1>&2 "*** Problem checking deps in \"$$dir\"." ; \
				exit 1; \
			fi; \
		fi; }
.endfor
.if ${NO_SHARED_LIBS:L} != "yes"
.  for _i in ${LIB_DEPENDS}
	@unset FLAVOUR SUBPACKAGE || true; \
	echo ${_i:Q}|{ \
		IFS=:; read dep pkg dir target; \
		${_flavour_fragment}; \
		libspecs=;comma=; \
		default=$$(eval $$toset ${MAKE} _print-packagename); \
		case "X$$pkg" in \
		X)	pkg=$$(echo $$default | sed -e 's,-[0-9].*,-*,');; \
		esac; \
		newdep=; comma=; \
		if ${PKG_CMD_INFO} -qe $$pkg; then \
			listlibs='ls /usr/lib $$shdir 2>/dev/null'; \
		else \
			listlibs='ls /usr/lib 2>/dev/null'; \
			IFS=,; for d in $$dep; do \
				${_libresolve_fragment}; \
				case "$$check" in \
				*.a|Missing\ library|Error:*) \
					newdep="$$newdep$$comma$$d"; \
					comma=',' ;; \
				esac; \
			done; \
			comma=; dep="$$newdep"; \
		fi; \
		if [[ -n $$newdep ]]; then \
			( unset PACKAGING || true; \
			  eval $$toset ${MAKE} \
			    ${PKGREPOSITORY}/$$default${PKG_SUFX} \
			); \
			listlibs='${SETENV} PATH=${PKG_CMDDIR:Q}:$$PATH \
			    ${PKG_CMD_INFO} -L \
			    ${PKGREPOSITORY}/$$default${PKG_SUFX} \
			    | grep $$shdir | sed -e "s,^$$shdir/,,"'; \
		fi; \
		IFS=,; for d in $$dep; do \
			${_libresolve_fragment}; \
			case "$$check" in \
			*.a) continue;; \
			Missing\ library|Error:*) \
				echo 1>&2 "Can't resolve libspec $$d"; \
				exit 1;; \
			*) \
				libspecs="$$libspecs$$comma$$shprefix$$check"; \
				comma=',';; \
			esac; \
		done; \
		case "X$$libspecs" in \
		X) ;;\
		*) \
			echo "@libdepend $$self:$$libspecs:$$pkg:$$default" \
			    >>$${_depends_result}; \
			if ! fgrep -q "|$$default|" $${_DEPENDS_FILE}; then \
				echo "lib|$$default|" >>$${_DEPENDS_FILE}; \
				toset="$$toset self=\"$$default\""; \
				if ! eval $$toset ${MAKE} \
				    _recurse-solve-package-depends; then  \
					echo 1>&2 "*** Problem checking deps in \"$$dir\"." ; \
					exit 1; \
				fi; \
			fi;; \
		esac; \
	}
.  endfor
.endif

# recursively build a list of dirs for package running, ready for tsort
_recurse-run-dir-depends:
.for _dir in ${_ALWAYS_DEP} ${_RUN_DEP}
	@unset FLAVOUR SUBPACKAGE || true; \
	echo "$$self ${_dir}"; \
	if ! fgrep -q "|${_dir}|" $${_DEPENDS_FILE}; then \
		echo "|${_dir}|" >>$${_DEPENDS_FILE}; \
		dir=${_dir}; \
		${_flavour_fragment}; \
		toset="$$toset self=\"${_dir}\""; \
		if ! eval $$toset ${MAKE} _recurse-run-dir-depends; then  \
			echo 1>&2 "*** Problem checking deps in \"$$dir\"."; \
			exit 1; \
		fi; \
	fi
.endfor

run-dir-depends:
.if !empty(_ALWAYS_DEP) || !empty(_RUN_DEP)
	@${_depfile_fragment}; \
	if ! fgrep -q "|${FULLPKGPATH}|" $${_DEPENDS_FILE}; then \
		echo "|${FULLPKGPATH}|" >>$${_DEPENDS_FILE}; \
		self=${FULLPKGPATH} PACKAGING=${SUBPACKAGE:Q} \
		${MAKE} _recurse-run-dir-depends; \
	fi
.else
	@echo "${FULLPKGPATH} ${FULLPKGPATH}"
.endif

# recursively build a list of dirs for package building, ready for tsort
# second and further stages need _RUN_DEP.
_recurse-all-dir-depends:
.for _dir in ${_ALWAYS_DEP} ${_BUILD_DEP} ${_RUN_DEP} ${_FETCH_DEP}
	@unset FLAVOUR SUBPACKAGE || true; \
	echo "$$self ${_dir}"; \
	if ! fgrep -q "|${_dir}|" $${_DEPENDS_FILE}; then \
		echo "|${_dir}|" >>$${_DEPENDS_FILE}; \
		dir=${_dir}; \
		${_flavour_fragment}; \
		toset="$$toset self=\"${_dir}\""; \
		if ! eval $$toset ${MAKE} _recurse-all-dir-depends; then  \
			echo 1>&2 "*** Problem checking deps in \"$$dir\"."; \
			exit 1; \
		fi; \
	fi
.endfor

# first stage does not need _RUN_DEP
_build-dir-depends:
.for _dir in ${_ALWAYS_DEP} ${_BUILD_DEP}
	@unset FLAVOUR SUBPACKAGE || true; \
	echo "$$self ${_dir}"; \
	if ! fgrep -q "|${_dir}|" $${_DEPENDS_FILE}; then \
		echo "|${_dir}|" >>$${_DEPENDS_FILE}; \
		dir=${_dir}; \
		${_flavour_fragment}; \
		toset="$$toset self=\"${_dir}\""; \
		if ! eval $$toset ${MAKE} _recurse-all-dir-depends; then  \
			echo 1>&2 "*** Problem checking deps in \"$$dir\"."; \
			exit 1; \
		fi; \
	fi
.endfor

build-dir-depends:
.if !empty(_ALWAYS_DEP) || !empty(_BUILD_DEP)
	@${_depfile_fragment}; \
	if ! fgrep -q "|${FULLPKGPATH}|" $${_DEPENDS_FILE}; then \
		echo "|${FULLPKGPATH}|" >>$${_DEPENDS_FILE}; \
		self=${FULLPKGPATH} ${MAKE} _build-dir-depends; \
	fi
.else
	@echo "${FULLPKGPATH} ${FULLPKGPATH}"
.endif

all-dir-depends:
.if !empty(_ALWAYS_DEP) || !empty(_BUILD_DEP) || !empty(_RUN_DEP) || !empty(_FETCH_DEP)
	@${_depfile_fragment}; \
	if ! fgrep -q "|${FULLPKGPATH}|" $${_DEPENDS_FILE}; then \
		echo "|${FULLPKGPATH}|" >>$${_DEPENDS_FILE}; \
		self=${FULLPKGPATH} ${MAKE} _recurse-all-dir-depends; \
	fi
.else
	@echo "${FULLPKGPATH} ${FULLPKGPATH}"
.endif

link-categories:
.for _CAT in ${CATEGORIES}
	@linkname=${PORTSDIR}/${_CAT}/$$(basename ${.CURDIR}); \
	if [ ! -e $$linkname ]; then \
		echo "$$linkname -> ${.CURDIR}"; \
		mkdir -p ${PORTSDIR}/${_CAT}; \
		ln -s ${.CURDIR} $$linkname; \
	fi
.endfor

unlink-categories:
.for _CAT in ${CATEGORIES}
	@linkname=${PORTSDIR}/${_CAT}/$$(basename ${.CURDIR}); \
	if [ -L $$linkname ]; then \
		echo "rm $$linkname"; \
		rm $$linkname; \
		if rmdir ${PORTSDIR}/${_CAT} 2>/dev/null; then \
			echo "rmdir ${PORTSDIR}/${_CAT}"; \
	    fi; \
	fi
.endfor

homepage-links:
.if defined(HOMEPAGE)
	@echo '<li><a href="'${HOMEPAGE:Q}'">'${PKGNAME:Q}'</a>'
.else
	@echo '<li>${PKGNAME}'
.endif

.if ${FAKE:L} == "no"
.  include "${PORTSDIR}/infrastructure/mk/old-install.mk"
.endif

#####################################################
# convenience targets, not really needed
#####################################################

checkpatch:
	@cd ${.CURDIR} && exec ${MAKE} PATCH_CHECK_ONLY=Yes patch

clean-depends:
	@cd ${.CURDIR} && exec ${MAKE} clean=depends

distclean:
	@cd ${.CURDIR} && exec ${MAKE} CLEANDEPENDS=No clean=dist

cleandir:
	@cd ${.CURDIR} && exec ${MAKE} CLEANDEPENDS=Yes clean

delete-package:
	@cd ${.CURDIR} && exec ${MAKE} CLEANDEPENDS=No clean=package

homepage:
.ifdef HOMEPAGE
	$${BROWSER:-lynx} ${HOMEPAGE:Q}
.else
	@echo This port has not defined a HOMEPAGE.
.endif

reinstall:
	@cd ${.CURDIR} && exec ${MAKE} clean='install force'
	@cd ${.CURDIR} && DEPENDS_TARGET=${DEPENDS_TARGET} exec ${MAKE} install

repackage:
	@cd ${.CURDIR} && exec ${MAKE} CLEANDEPENDS=No clean=packages
	@cd ${.CURDIR} && exec ${MAKE} package

rebuild:
	@rm -f ${_BUILD_COOKIE}
	@cd ${.CURDIR} && exec ${MAKE} build

uninstall deinstall:
	@${ECHO_MSG} "===> Deinstalling for ${FULLPKGNAME${SUBPACKAGE}}"
	@${SUDO} ${SETENV} PATH=${PKG_CMDDIR:Q}:$$PATH \
	    ${PKG_CMD_DELETE} ${FULLPKGNAME${SUBPACKAGE}}

upgrade:
	@exec ${MAKE} _UPGRADE_FLAGS= _do-upgrade

reupgrade:
	@exec ${MAKE} _UPGRADE_FLAGS=-af _do-upgrade

_do-upgrade: _upgrade_pkgs .WAIT _upgrade ${_UPGRADE_DEPS}

_upgrade_pkgs:
	@i=0; for f in ${PKGFILE} ${_UPGRADE_PKGS}; do \
		[[ -s $$f ]] || i=1; \
	done; [[ $$i = 0 ]] || exec ${MAKE} ${_PACKAGE_COOKIES}
	@${ECHO_MSG} "===>  Upgrading for ${FULLPKGNAME}${_MASTER}"

_upgrade:
	${SUDO} ${PKG_CMD_UPGRADE} ${_UPGRADE_FLAGS} ${PKGFILE${SUBPACKAGE}}

.if defined(ERRORS)
.BEGIN:
.  for _m in ${ERRORS}
	@echo 1>&2 ${_m} "(in ${PKGPATH})"
.  endfor
	@exit 1
.endif

.PHONY: \
	_build-dir-depends _delete-package-links \
	_fetch-makefile _fetch-onefile \
	_package _package-links _print-packagename \
	_recurse-all-dir-depends _recurse-lib-depends-check \
	_recurse-run-dir-depends _recurse-solve-package-depends _refetch \
	addsum \
	all all-dir-depends build \
	build-depends build-depends-list build-dir-depends \
	checkpatch checksum clean cleandir \
	clean-depends configure deinstall \
	delete-package \
	depends \
	describe distclean distpatch \
	do-build do-configure do-distpatch \
	do-extract do-fetch do-install \
	do-package do-regress extract \
	fake fetch fetch-all \
	fetch-makefile for-all-depends for-build-depends \
	for-run-depends full-all-depends full-build-depends \
	full-run-depends homepage homepage-links install install-binpkg \
	lib-depends lib-depends-check lib-depends-list \
	link-categories makesum manpages-check \
	package patch \
	plist post-build post-configure \
	post-distpatch post-extract post-fetch \
	post-install post-package post-patch \
	post-regress pre-build pre-configure \
	pre-extract pre-fake pre-fetch \
	pre-install pre-package pre-patch \
	pre-regress print-build-depends print-run-depends \
	_print-uses readmes rebuild \
	regress regress-depends \
	reinstall repackage reupgrade run-depends \
	run-depends-list run-dir-depends show \
	uninstall unlink-categories update-patches update-plist \
	upgrade _upgrade _upgrade_pkgs unconfigure \
	relevant-checks _relevant-checks
