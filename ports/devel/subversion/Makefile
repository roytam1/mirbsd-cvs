# $MirOS: ports/devel/subversion/Makefile,v 1.7 2006/06/04 20:29:35 bsiegert Exp $

COMMENT=			Subversion revision control system
VERSION=		1.3.2
DASH_VER=		-0
DISTNAME=		subversion-${VERSION}
PKGNAME=		subversion-${VERSION}${DASH_VER}
CATEGORIES=		devel net

HOMEPAGE=		http://subversion.tigris.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://subversion.tigris.org/tarballs/
EXTRACT_SUFX=		.tar.bz2

FLAVORS=		bsddb
FLAVOR?=

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		neon::net/neon
RUN_DEPENDS+=		:p5-URI-*:www/p5-URI
MODULES=		textproc/expat

.if ${FLAVOR:L:Mbsddb}
LIB_DEPENDS+=		db.4.2::databases/db

CONFIGURE_ARGS+=	--with-dbm=db42 --with-berkeley-db
.else
CONFIGURE_ARGS+=	--without-berkeley-db
.endif


#
# We don't support building the apache module (yet).
#
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-neon=${LOCALBASE}
CONFIGURE_ARGS+=	--with-gdbm=no
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--with-expat=${EXPAT_PREFIX}
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/apr ${WRKSRC}/apr-util
MAKE_ENV+=		LD_LIBRARY_PATH=${WRKINST}${LOCALBASE}/lib

# Workaround for autotools madness
post-patch:
	rm -rf ${WRKSRC}/apr-util/autom4te.cache

post-build:
	nroff -mdoc ${FILESDIR}/svnup-cvs.1 > ${WRKSRC}/contrib/client-side/svnup-cvs.cat1

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/client-side/svn_load_dirs.pl ${PREFIX}/bin/svn_load_dirs
	${INSTALL_SCRIPT} ${FILESDIR}/svnup-cvs ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/contrib/client-side/svnup-cvs.cat1 ${PREFIX}/man/cat1/svnup-cvs.0

.include <bsd.port.mk>
