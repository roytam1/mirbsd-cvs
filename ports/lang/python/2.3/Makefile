# $MirOS: ports/lang/python/2.3/Makefile,v 1.8 2007/12/29 16:57:34 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2005/08/27 15:57:31 naddy Exp $

VERSION=		2.3
PATCHLEVEL=		.7
DASH_VER=		0

COMMENT-bsddb=		Berkeley db module for Python
COMMENT-expat=		expat module for Python
COMMENT-gdbm=		GNU dbm module for Python
COMMENT-idle=		IDE for Python
COMMENT-mpz=		GNU arbitrary magnitude integer module for Python
COMMENT-tests=		Python test suite
COMMENT-tkinter=	tk GUI module for Python
COMMENT-tools=		extra tools for Python

FLAVOURS+=		no_bsddb no_cxx no_expat no_gdbm no_idle no_mpz no_tkinter
FLAVOUR?=		no_bsddb

.if ${FLAVOUR:L:Mno_cxx}
FLAVOUR+=		no_bsddb no_expat no_gdbm no_idle no_mpz no_tkinter
CONFIGURE_ARGS+=	--without-cxx
MULTI_PACKAGES=
.else
USE_CXX=		Yes
MULTI_PACKAGES=		-tests -tools
.endif

SUBPACKAGE?=

.if defined(PACKAGING)
#  All subpackages depend on the main python package.
.  if !empty(SUBPACKAGE)
.    if ${FLAVOUR:L:Mno_cxx}
RUN_DEPENDS+=		::lang/python/${VERSION},no_cxx
.    else
RUN_DEPENDS+=		::lang/python/${VERSION}
.    endif
LIB_DEPENDS=
.  endif
.endif

# On architectures with shared libs, no_xxx flavours are a convenient
# way to avoid pulling in dependencies, and don't actually show up
# in the final package names.  On architectures without shared libs,
# no_xxx flavours dictate what gets linked into the Python binary.

.if empty(FLAVOUR:L:Mno_bsddb)
.  if ${FLAVOUR:L:Mno_cxx}
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

.if empty(FLAVOUR:L:Mno_gdbm)
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

.if empty(FLAVOUR:L:Mno_idle) && empty(FLAVOUR:L:Mno_tkinter)
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
MULTI_PACKAGES+=	-idle
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-idle"
RUN_DEPENDS+=		::lang/python/${VERSION},-tkinter
.endif

.if empty(FLAVOUR:L:Mno_tkinter)
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

.if empty(FLAVOUR:L:Mno_mpz) && ${VERSION} == "2.3"
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

.if empty(FLAVOUR:L:Mno_expat) && ${VERSION} == "2.3"
SETUP_LOCAL+=		Setup.expat
.  if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
.    if !defined(PACKAGING)
MODULES+=		textproc/expat
.    endif
MULTI_PACKAGES+= 	-expat
.  else
MODULES+=		textproc/expat
.  endif
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-expat"
MODULES+=		textproc/expat
.endif

# Strip off no_xxx flavours from the package name if we are not
# building the "monster" Python for platforms without shared libraries.

.if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:U} != YES
FULLPKGNAME=		${PKGNAME}${FLAVOUR_EXT:S/-no_bsddb//:S/-no_expat//:S/-no_gdbm//:S/-no_idle//:S/-no_mpz//:S/-no_tkinter//}
.endif

FULLPKGNAME-bsddb=	python-bsddb-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-expat=	python-expat-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-gdbm=	python-gdbm-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-idle=	python-idle-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-mpz=	python-mpz-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-tests=	python-tests-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-tkinter=	python-tkinter-${VERSION}${PATCHLEVEL}-${DASH_VER}
FULLPKGNAME-tools=	python-tools-${VERSION}${PATCHLEVEL}-${DASH_VER}

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



.include <bsd.port.mk>
