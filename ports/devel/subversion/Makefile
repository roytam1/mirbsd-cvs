# $MirOS: ports/devel/subversion/Makefile,v 1.22 2009/07/29 20:31:27 bsiegert Exp $

COMMENT=		Subversion revision control system
VERSION=		1.5.2
DASH_VER=		2
DISTNAME=		subversion-${VERSION}
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

FLAVOURS=		bsddb
FLAVOUR?=

LIB_DEPENDS+=		apr::devel/apr/apr
LIB_DEPENDS+=		neon::net/neon
RUN_DEPENDS+=		:p5-URI-*:www/p5-URI
MODULES+=		p5

.if ${FLAVOUR:L:Mbsddb}
LIB_DEPENDS+=		db.4.2::databases/db
LIB_DEPENDS+=		aprutil::devel/apr/util,bsddb
CONFIGURE_ARGS+=	--with-berkeley-db
.else
LIB_DEPENDS+=		aprutil::devel/apr/util
CONFIGURE_ARGS+=	--without-berkeley-db
.endif

# We don't support building the apache module (yet).
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
MODULES+=		p5

CONFIGURE_ARGS+=	--with-neon=${LOCALBASE}
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

DOCFILES=		svnsync.txt fsfs ssh-tricks

post-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} swig-pl
	${NROFF} -mdoc ${FILESDIR}/svnup-cvs.1 >${WRKBUILD}/contrib/client-side/svnup-cvs.cat1

post-install:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} \
	${MAKE_PROGRAM} install-swig-pl \
	INSTALLSITELIB=${PREFIX:Q}/${P5SITE} \
        INSTALLSITEARCH="\$${INSTALLSITELIB}/${MODPERL_ARCH}" \
        INSTALLBIN=${TRUEPREFIX:Q}/bin INSTALLSCRIPT='$${INSTALLBIN}' \
        INSTALLMAN3DIR=${PREFIX:Q}/man/man3 \
        INSTALLSITEMAN3DIR=${PREFIX:Q}/man/man3 \
        INSTALLVENDORMAN3DIR=${PREFIX:Q}/man/man3
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/client-side/svn_load_dirs/svn_load_dirs.pl ${PREFIX}/bin/svn_load_dirs
	${INSTALL_SCRIPT} ${FILESDIR}/svnup-cvs ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/contrib/client-side/svnup-cvs.cat1 ${PREFIX}/man/cat1/svnup-cvs.0
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/subversion
	${INSTALL_DATA} ${WRKSRC}/contrib/client-side/svn_load_dirs/svn_load_dirs.README ${PREFIX}/share/doc/subversion
.for i in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/notes/${i} ${PREFIX}/share/doc/subversion
.endfor

.include <bsd.port.mk>
