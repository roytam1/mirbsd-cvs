# $MirOS: ports/databases/sqlite/Makefile,v 1.11 2008/02/28 18:27:21 tg Exp $

COMMENT=		Embedded SQL implementation
COMMENT-lemon=		Lightweight parser
_V=			3.3.17
DASH_VER=		2
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}-${DASH_VER}
PKGNAME-lemon=		lemon-${_V}-${DASH_VER}
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

# Public Domain
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MULTI_PACKAGES+=	-lemon
SUBPACKAGE?=

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-static \
			--disable-tcl

NO_REGRESS=		Yes

UMAKE=			${SETENV} ${MAKE_ENV} ${MAKE}

post-extract:
	cp ${FILESDIR}/regexp.* ${WRKSRC}/src/
	cp ${FILESDIR}/{Makefile.lemon,lemon.1} ${WRKSRC}/tool/

post-build:
	cd ${WRKBUILD}/tool && \
	    ${UMAKE} -f Makefile.lemon obj && \
	    ${UMAKE} -f Makefile.lemon BSD_PREFIX=${TRUEPREFIX:Q} depend && \
	    ${UMAKE} -f Makefile.lemon BSD_PREFIX=${TRUEPREFIX:Q}

post-install:
	${INSTALL_MAN} ${WRKSRC}/sqlite3.1 ${PREFIX}/man/man1/
	cd ${WRKBUILD}/tool && ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} \
	    ${MAKE} -f Makefile.lemon BSD_PREFIX=${TRUEPREFIX:Q} install
	${INSTALL_DATA_DIR} ${PREFIX}/share/lemon
	${INSTALL_DATA} ${WRKSRC}/tool/lempar.c ${PREFIX}/share/lemon/

.include <bsd.port.mk>
