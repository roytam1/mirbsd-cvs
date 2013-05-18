# $MirOS: ports/lang/python/Makefile.inc,v 1.21 2009/05/30 20:38:24 tg Exp $
# $OpenBSD: Makefile.inc,v 1.32 2005/06/06 20:47:04 alek Exp $

.include <mirports.sys.mk>

# IMPORTANT!  If you make any changes to the Python ports, be sure
# to also update files/CHANGES.MirPorts for your change.  This is a
# requirement of the PSF license, if it constitutes a change to
# Python itself.

COMMENT=		interpreted object-oriented programming language

PKGNAME=		python-${VERSION}${PATCHLEVEL}-${DASH_VER}
DISTNAME=		Python-${VERSION}${PATCHLEVEL}
CATEGORIES=		lang
MASTER_SITES=		http://www.python.org/ftp/${PSUBDIR}/
PSUBDIR=		python/${VERSION}${PATCHLEVEL}
EXTRACT_SUFX=		.tgz

HOMEPAGE=		http://www.python.org/

# PSF license <http://www.python.org/${VERSION}/license.html>
# A summary of changes to Python is required to be distributed
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		bz2::archivers/bzip2

# Python wants GNU libreadline so badly.
MODULES+=		devel/libreadline
CPPFLAGS+=		-I${WRKDIR:Q}/include	# XXX hack, see below

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
# --srcdir is needed for systrace to work correctly
CONFIGURE_ARGS+=	--with-fpectl --with-threads --srcdir=${WRKSRC:Q}
.if ${OStype:NInterix:NDarwin}
CONFIGURE_ARGS+=	--enable-ipv6
.endif
.if ${OStype:MDarwin}
CONFIGURE_ARGS+=	MACOSX_DEPLOYMENT_TARGET=
.endif

# THREAD_STACK_SIZE value might be changed by particular python release
THREAD_STACK_SIZE?=	0x20000		# increase this for zope

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

# Same algorithm as in configure
_MD_SYSTEM!=	uname -s | tr -d '[/ ]' | tr '[[A-Z]]' '[[a-z]]'
_MD_RELEASE!=	uname -r | tr -d '[/ ]' | sed 's/^[[A-Z]]\.//' | sed 's/\..*//'
.if ${OStype:MDarwin}
MACHDEP=	${_MD_SYSTEM}
.else
MACHDEP=	${_MD_SYSTEM}${_MD_RELEASE}
.endif
SUBST_VARS+=	MACHDEP PATCHLEVEL

post-extract:
	mkdir -p ${WRKDIR}/include
	ln -s ${LOCALBASE}/include/readline ${WRKDIR}/include/

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/Tools/scripts/pydoc \
		${PREFIX}/bin/pydoc${VERSION}
	if [ -f ${FILESDIR}/idle ] ; then \
	sed -e "s,@VERSION@,${VERSION},g" -e "s,@LOCALBASE@,${LOCALBASE},g" \
		${FILESDIR}/idle >${WRKSRC}/idle ; \
	${INSTALL_SCRIPT} ${WRKSRC}/idle ${PREFIX}/bin/idle${VERSION} ; \
	fi
	cd ${WRKSRC}; tar -cf - Tools | (cd ${PREFIX}/lib/python${VERSION}; \
		tar -xf -)
	${INSTALL_DATA} ${WRKSRC}/libpython${VERSION}.a \
		${PREFIX}/lib/python${VERSION}/config
	if [ -f ${PREFIX}/lib/python${VERSION}/config/libpython${VERSION}.so.0.0 ]; then \
		cd ${PREFIX}/lib && ln -s python${VERSION}/config/libpython${VERSION}.so.0.0; \
	fi
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/python${VERSION}
	${INSTALL_DATA} ${FILESDIR}/CHANGES.* \
	    ${PREFIX}/share/doc/python${VERSION}/
