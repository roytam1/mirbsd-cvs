# $MirOS: ports/databases/sqlite/Makefile,v 1.14 2013/07/03 20:49:28 tg Exp $

COMMENT=		Embedded SQL implementation
COMMENT-lemon=		Lightweight parser
_V=			3.6.1
DASH_VER=		1
DISTNAME=		sqlite-${_V}
PKGNAME=		sqlite3-${_V}-${DASH_VER}
PKGNAME-lemon=		lemon-${_V}-${DASH_VER}
CATEGORIES=		databases
HOMEPAGE=		http://www.sqlite.org/
MASTER_SITES=		${HOMEPAGE}

# positively hostile fake-“Public Domain” with contradiction in itself
PERMIT_DISTFILES_CDROM=	hostile PD
PERMIT_DISTFILES_FTP=	hostile PD
PERMIT_PACKAGE_CDROM=	hostile PD
PERMIT_PACKAGE_FTP=	hostile PD

MULTI_PACKAGES+=	-lemon
SUBPACKAGE?=

CONFIGURE_STYLE=	autoconf detectheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-static \
			--enable-threadsafe \
			--enable-cross-thread-connections \
			--enable-threads-override-locks \
			--enable-tempstore \
			--disable-tcl \
			--enable-load-extension

NO_REGRESS=		Yes

UMAKE=			${SETENV} ${MAKE_ENV} ${MAKE}

post-extract:
	rm -f ${WRKSRC}/aclocal.m4; touch ${WRKSRC}/aclocal.m4	# too new
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
