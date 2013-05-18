# $MirOS: ports/lang/python/Makefile.inc,v 1.7 2005/11/16 19:08:22 tg Exp $
# $OpenBSD: Makefile.inc,v 1.32 2005/06/06 20:47:04 alek Exp $

.include <mirports.sys.mk>

# IMPORTANT!  If you make any changes to the Python ports, be sure
# to also update files/CHANGES.MirPorts for your change.  This is a
# requirement of the PSF license, if it constitutes a change to
# Python itself.

COMMENT=			interpreted object-oriented programming language
COMMENT-bsddb=			Berkeley db module for Python
COMMENT-expat=			expat module for Python
COMMENT-gdbm=			GNU dbm module for Python
COMMENT-idle=			IDE for Python
COMMENT-mpz=			GNU arbitrary magnitude integer module for Python
COMMENT-tests=			Python test suite
COMMENT-tkinter=			tk GUI module for Python
COMMENT-tools=			extra tools for Python

PKGNAME=	python-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
DISTNAME=	Python-${VERSION}${PATCHLEVEL}
CATEGORIES=	lang
MASTER_SITES=	ftp://ftp.python.org/pub/${PSUBDIR}/ \
		http://python.mirrors.pair.com/ftp/${PSUBDIR}/ \
		http://python.mirrors.ilisys.com.au/ftp/${PSUBDIR}/
PSUBDIR=	python/${VERSION}${PATCHLEVEL}
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://www.python.org/
RESPONSIBLE=	Benny Siegert <bsiegert@gmx.de>

# PSF license <http://www.python.org/${VERSION}/license.html>
# A summary of changes to Python is required to be distributed
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS+=		no_bsddb no_cxx no_expat no_gdbm no_idle no_mpz no_tkinter
FLAVOR?=

.if ${FLAVOR:L:Mno_cxx}
FLAVOR+=		no_bsddb no_expat no_gdbm no_idle no_mpz no_tkinter
CONFIGURE_ARGS+=	--without-cxx
MULTI_PACKAGES=
.else
USE_CXX=		Yes
MULTI_PACKAGES=		-tests -tools
.endif

SUBPACKAGE?=

LIB_DEPENDS+=		bz2::archivers/bzip2

# Python wants GNU libreadline so badly.
# XXX both PSF and FSF say Python licence is GPL compatible,
# XXX but I doubt it a little. -mirabile
LIB_DEPENDS+=		readline.5::devel/libreadline
CPPFLAGS+=		-I${WRKDIR}/include	# XXX hack, see below

.if defined(PACKAGING)
#  All subpackages depend on the main python package.
.  if !empty(SUBPACKAGE)
.    if ${FLAVOR:L:Mno_cxx}
RUN_DEPENDS+=		::lang/python/${VERSION},no_cxx
.    else
RUN_DEPENDS+=		::lang/python/${VERSION}
.    endif
LIB_DEPENDS=
.  endif
.endif

# On architectures with shared libs, no_xxx flavors are a convenient
# way to avoid pulling in dependencies, and don't actually show up
# in the final package names.  On architectures without shared libs,
# no_xxx flavors dictate what gets linked into the Python binary.

.if empty(FLAVOR:L:Mno_bsddb)
.  if ${FLAVOR:L:Mno_cxx}
BUILD_DEPENDS+=		::databases/db,no_cxx
.  else
BUILD_DEPENDS+=		::databases/db
.  endif
SETUP_LOCAL+=		Setup.bsddb
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+=	-bsddb
.  else
LIB_DEPENDS+=		db.4.2::databases/db
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-bsddb"
LIB_DEPENDS+=		db.4.2::databases/db
.endif

.if empty(FLAVOR:L:Mno_gdbm)
BUILD_DEPENDS+=		::databases/gdbm
SETUP_LOCAL+=		Setup.gdbm
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+=	-gdbm
.  else
LIB_DEPENDS+=		gdbm.3::databases/gdbm
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-gdbm"
LIB_DEPENDS+=		gdbm.3::databases/gdbm
.endif

.if empty(FLAVOR:L:Mno_idle) && empty(FLAVOR:L:Mno_tkinter)
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+=	-idle
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-idle"
RUN_DEPENDS+=		::lang/python/${VERSION},-tkinter
.endif

.if empty(FLAVOR:L:Mno_tkinter)
USE_X11=		Yes
BUILD_DEPENDS+=		::x11/tk/8.4
SETUP_LOCAL+=		Setup.tkinter
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+=	-tkinter
SED_PLIST+=		| sed -e '/^%%tkinter%%/d' \
			| sed -e '/^%%tkinter_no_shared%%/r${PKGDIR}/PFRAG-tkinter.no_shared' -e '//d'
.  else
SED_PLIST+=		| sed -e '/^%%tkinter%%/r${PKGDIR}/PFRAG-tkinter.no_shared' -e '//d'
LIB_DEPENDS+=		tk84::x11/tk/8.4
.  endif
.else
SED_PLIST+=		| sed -e '/^%%tkinter%%/d'
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-tkinter"
LIB_DEPENDS+=		tk84::x11/tk/8.4
.endif

.if empty(FLAVOR:L:Mno_mpz) && ${VERSION} == "2.3"
BUILD_DEPENDS+=		::devel/gmp
SETUP_LOCAL+=		Setup.mpz
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+= 	-mpz
.  else
LIB_DEPENDS+=		gmp::devel/gmp
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-mpz"
LIB_DEPENDS+=		gmp::devel/gmp
.endif

.if empty(FLAVOR:L:Mno_expat) && ${VERSION} == "2.3"
SETUP_LOCAL+=		Setup.expat
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
.    if !defined(PACKAGING)
LIB_DEPENDS+=		expat.4.0:expat->=1.95.6:textproc/expat
.    endif
MULTI_PACKAGES+= 	-expat
.  else
LIB_DEPENDS+=		expat.4.0:expat->=1.95.6:textproc/expat
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-expat"
LIB_DEPENDS+=		expat.4.0:expat->=1.95.6:textproc/expat
.endif

# Strip off no_xxx flavors from the package name if we are not
# building the "monster" Python for platforms without shared libraries.

.if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
FULLPKGNAME=		${PKGNAME}${FLAVOR_EXT:S/-no_bsddb//:S/-no_expat//:S/-no_gdbm//:S/-no_idle//:S/-no_mpz//:S/-no_tkinter//}
.endif

FULLPKGNAME-bsddb=	python-bsddb-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-expat=	python-expat-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-gdbm=	python-gdbm-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-idle=	python-idle-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-mpz=	python-mpz-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-tests=	python-tests-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-tkinter=	python-tkinter-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}
FULLPKGNAME-tools=	python-tools-${VERSION}${PATCHLEVEL}${PKG_PATCHLEVEL}

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
# --srcdir is needed for systrace to work correctly
CONFIGURE_ARGS+=	--with-fpectl --with-threads --srcdir=${WRKSRC}
CONFIGURE_ARGS+=	--enable-ipv6

# THREAD_STACK_SIZE value might be changed by particular python release
THREAD_STACK_SIZE?=	0x20000

REGRESS_TARGET=		test

.for _i in ${MACHINE_ARCH} ${ARCH}
.  if !empty(LP64_PLATFORMS:M${OStype}\:${_i})
NO64BIT=	\#
.  endif
.endfor

.ifdef NO64BIT
SED_PLIST+=	-e '/%%mm%%/d'
.else
SED_PLIST+=	-e '/%%mm%%/r${PKGDIR}/PFRAG.mm' -e '//d'
.endif

.if ${OStype} == "MirBSD"
NONIS=		\#
SED_PLIST+=	| sed -e '/^IFNIS:/d'
.else
SED_PLIST+=	| sed -e '/^IFNIS:/s///'
.endif

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:U} == YES
NOSHARED=	\#
CONFIGURE_ENV+=	OPT='${CFLAGS}' LDFLAGS='-L${WRKSRC}'
.else
CONFIGURE_ENV+= OPT='${CFLAGS} -DTHREAD_STACK_SIZE=${THREAD_STACK_SIZE} ${PICFLAG}'
LDFLAGS+=	-L${WRKSRC}
MAKE_FLAGS+=	MAJOR=0 MINOR=0 LDLIBRARY=libpython${VERSION}.so.0.0 \
		LD_LIBRARY_PATH=${WRKSRC} PATH="${WRKDIST}:${PORTPATH}"
FAKE_FLAGS+=	MAJOR=0 MINOR=0 LDLIBRARY=libpython${VERSION}.so.0.0 \
		LD_LIBRARY_PATH=${WRKSRC} RANLIB=:
.endif

# Same algorithm as in configure
_MD_SYSTEM!=	uname -s | tr -d '[/ ]' | tr '[[A-Z]]' '[[a-z]]'
_MD_RELEASE!=	uname -r | tr -d '[/ ]' | sed 's/^[[A-Z]]\.//' | sed 's/\..*//'
MACHDEP=	${_MD_SYSTEM}${_MD_RELEASE}
SUBST_VARS+=	MACHDEP

post-extract:
	# XXX hack
	mkdir -p ${WRKDIR}/include
	ln -s ${LOCALBASE}/include/readline ${WRKDIR}/include/
	# XXX endhack

post-configure:
	@sed -e 's,@NOSHARED@,${NOSHARED},g'	\
	     -e 's,@NO64BIT@,${NO64BIT},g'	\
	     -e 's,@NONIS@,${NONIS},g'		\
		${FILESDIR}/Setup >${WRKSRC}/Modules/Setup
.for file in ${SETUP_LOCAL}
	@sed -e 's,@NOSHARED@,${NOSHARED},g'	\
		${FILESDIR}/${file} >>${WRKSRC}/Modules/Setup.local
.endfor
	@cd ${WRKSRC} && ${MAKE_PROGRAM} Makefile

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/Tools/scripts/pydoc \
		${PREFIX}/bin/pydoc${VERSION}
	@sed -e "s,@VERSION@,${VERSION},g" -e "s,@LOCALBASE@,${LOCALBASE},g" \
		${FILESDIR}/idle >${WRKSRC}/idle
	${INSTALL_SCRIPT} ${WRKSRC}/idle ${PREFIX}/bin/idle${VERSION}
	@cd ${WRKSRC}; tar -cf - Tools | (cd ${PREFIX}/lib/python${VERSION}; \
		tar -xf -)
	${INSTALL_DATA} ${WRKSRC}/libpython${VERSION}.a \
		${PREFIX}/lib/python${VERSION}/config
	@if [ -f ${PREFIX}/lib/python${VERSION}/config/libpython${VERSION}.so.0.0 ]; then \
		cd ${PREFIX}/lib && ln -s python${VERSION}/config/libpython${VERSION}.so.0.0; \
	fi
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/python${VERSION}
	${INSTALL_DATA} ${FILESDIR}/CHANGES.OpenBSD \
		${PREFIX}/share/doc/python${VERSION}/CHANGES.OpenBSD
	[[ ! -f ${FILESDIR}/CHANGES.MirPorts ]] || \
	    ${INSTALL_DATA} ${FILESDIR}/CHANGES.MirPorts \
	    ${PREFIX}/share/doc/python${VERSION}/
