# $MirOS: ports/devel/subversion/Makefile,v 1.16 2008/03/09 17:22:33 tg Exp $

COMMENT=		Subversion revision control system
VERSION=		1.4.5
DASH_VER=		0
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

CONFIGURE_ARGS+=	--with-neon=${LOCALBASE}
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

DOCFILES=		svnsync.txt fsfs ssh-tricks

MODULES+=		p5
# We have to replicate some of the perl.port.mk logic here.
P5MAN3EXT!=		/usr/bin/perl -e 'use Config; print ".".$$Config{man3ext};'
P5DLEXT!=		/usr/bin/perl -e 'use Config; print ".".$$Config{dlext};'
SUBST_VARS+=		P5SITE P5MAN3EXT P5DLEXT

post-build:
	cd ${WRKBUILD} && ${MAKE_PROGRAM} swig-pl
	nroff -mdoc ${FILESDIR}/svnup-cvs.1 > ${WRKSRC}/contrib/client-side/svnup-cvs.cat1

# Use of LOCALBASE is intentional so that DESTDIR is not added twice.
post-install:
	cd ${WRKBUILD} && ${MAKE_PROGRAM} install-swig-pl \
	INSTALLSITELIB=${LOCALBASE:Q}/${P5SITE} \
        INSTALLSITEARCH="\$${INSTALLSITELIB}/${MODPERL_ARCH}" \
        INSTALLBIN=${LOCALBASE:Q}/bin INSTALLSCRIPT='$${INSTALLBIN}' \
        INSTALLMAN3DIR=${LOCALBASE:Q}/man/man3 \
        INSTALLSITEMAN3DIR=${LOCALBASE:Q}/man/man3 \
        INSTALLVENDORMAN3DIR=${LOCALBASE:Q}/man/man3
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/client-side/svn_load_dirs.pl ${PREFIX}/bin/svn_load_dirs
	${INSTALL_SCRIPT} ${FILESDIR}/svnup-cvs ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/contrib/client-side/svnup-cvs.cat1 ${PREFIX}/man/cat1/svnup-cvs.0
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/subversion
.for i in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/notes/${i} ${PREFIX}/share/doc/subversion
.endfor

.include <bsd.port.mk>
