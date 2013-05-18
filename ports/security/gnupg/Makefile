# $MirOS: ports/security/gnupg/Makefile,v 1.18 2007/04/13 19:27:22 bsiegert Exp $
# $OpenBSD: Makefile,v 1.52 2005/05/17 15:08:34 martin Exp $

COMMENT=		GNU privacy guard - PGP replacement under GPL
VERSION=		1.4.7
DISTNAME=		gnupg-${VERSION}
CATEGORIES=		security
HOMEPAGE=		http://www.gnupg.org/
MASTER_SITES=		http://ftp.gnupg.org/gcrypt/gnupg/ \
			ftp://ftp.gnupg.org/gcrypt/gnupg/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/gnupg/ \
			ftp://sunsite.dk/pub/security/gcrypt/gnupg/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/gnupg/ \
			ftp://pgp.iijlab.net/pub/pgp/gnupg/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/gnupg/

MASTER_SITES0=		http://www.gnupg.dk/contrib-dk/ \
			ftp://ftp.gnupg.dk/pub/contrib-dk/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		converters/libiconv
LIB_DEPENDS+=		bz2::archivers/bzip2
LIB_DEPENDS+=		usb::devel/libusb
B_R_DEPENDS+=		::archivers/mircpio
USE_CXX=		Yes # depends on libusb, which uses CXX
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
AUTOGEN=		${SHELL} ${WRKSRC}/scripts/autogen.sh
CONFIGURE_ARGS+=	--enable-static-rnd=linux \
			--disable-ldap \
			--disable-generic \
			--enable-mailto \
			--disable-nls \
			--enable-noexecstack \
			--without-included-zlib \
			--without-libcurl \
			--without-included-regex \
			--with-tar=${LOCALBASE:Q}/bin/tar
.if ${MACHINE_ARCH} == "m68k"
CONFIGURE_ARGS+=	--disable-asm
.endif
# libedit is *not* enough here.
CONFIGURE_ARGS+=	--without-readline

.if ${MACHINE_OS} == "BSD"
# cought by systrace
CONFIGURE_ENV+=		gnupg_cv_ipc_rmid_deferred_release=no
.endif

FLAVOURS=		no_idea

.include <mirports.sys.mk>

.if ${MKC_USAP:L} == "yes"
FLAVOUR?=		no_idea
.else
FLAVOUR?=
.endif

.if ${FLAVOUR:L:Mno_idea}
SUPDISTFILES=		idea.c.gz:0
CONFIGURE_ARGS+=	--disable-idea
.else
PERMIT_PACKAGE_CDROM=	http://www.mediacrypt.com/engl/Content/licensing_policy.htm
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} idea.c.gz:0
CONFIGURE_ARGS+=	--enable-idea
.endif

post-extract:
	@rm -f ${WRKSRC}/cipher/idea.c
.if !${FLAVOUR:L:Mno_idea}
	ln -s ${WRKDIR}/idea.c ${WRKSRC}/cipher/idea.c
.endif

DOCFILES=	AUTHORS BUGS NEWS PROJECTS README THANKS TODO \
		doc/DETAILS doc/HACKING doc/OpenPGP doc/highlights-1.4.txt

post-install:
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCFILES} ${PREFIX}/share/gnupg/

.include <bsd.port.mk>
