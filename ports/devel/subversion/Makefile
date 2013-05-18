# $MirOS: ports/devel/subversion/Makefile,v 1.10 2006/10/11 15:30:10 bsiegert Exp $

COMMENT=		Subversion revision control system
VERSION=		1.4.2
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

LIB_DEPENDS+=		apr::devel/apr/apr
LIB_DEPENDS+=		neon::net/neon
RUN_DEPENDS+=		:p5-URI-*:www/p5-URI

.if ${FLAVOR:L:Mbsddb}
LIB_DEPENDS+=		db.4.2::databases/db
LIB_DEPENDS+=		aprutil::devel/apr/util,bsddb
CONFIGURE_ARGS+=	--with-berkeley-db
.else
LIB_DEPENDS+=		aprutil::devel/apr/util
CONFIGURE_ARGS+=	--without-berkeley-db
.endif


#
# We don't support building the apache module (yet).
#
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-neon=${LOCALBASE}
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

DOCFILES=		svnsync.txt fsfs ssh-tricks

# Workaround for autotools madness
post-patch:
	rm -rf ${WRKSRC}/apr-util/autom4te.cache

post-build:
	nroff -mdoc ${FILESDIR}/svnup-cvs.1 > ${WRKSRC}/contrib/client-side/svnup-cvs.cat1

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/client-side/svn_load_dirs.pl ${PREFIX}/bin/svn_load_dirs
	${INSTALL_SCRIPT} ${FILESDIR}/svnup-cvs ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/contrib/client-side/svnup-cvs.cat1 ${PREFIX}/man/cat1/svnup-cvs.0
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/subversion
.for i in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/notes/${i} ${PREFIX}/share/doc/subversion
.endfor

.include <bsd.port.mk>
