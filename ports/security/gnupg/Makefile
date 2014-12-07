# $MirOS: ports/security/gnupg/Makefile,v 1.26 2013/07/28 17:59:53 tg Exp $
# $OpenBSD: Makefile,v 1.52 2005/05/17 15:08:34 martin Exp $

COMMENT=		GNU privacy guard - PGP replacement under GPLv3
DISTNAME=		gnupg-1.4.14
CATEGORIES=		security
HOMEPAGE=		https://www.gnupg.org/
MASTER_SITES=		http://ftp.gnupg.org/gcrypt/gnupg/ \
			ftp://ftp.gnupg.org/gcrypt/gnupg/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/gnupg/ \
			ftp://sunsite.dk/pub/security/gcrypt/gnupg/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/gnupg/ \
			ftp://pgp.iijlab.net/pub/pgp/gnupg/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/gnupg/

# GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

FLAVOURS=		big static
FLAVOUR?=

.if ${FLAVOUR:L:Mstatic}
LDFLAGS+=		-static
.endif

.if ${MACHINE_OS} == "BSD"
.  if ${MACHINE_ARCH} == "sparc"
GPG_USE_LIBUSB=		No
.  endif
.endif
.if ${FLAVOUR:L:Mbig}
GPG_USE_LIBUSB?=	Yes
.endif
GPG_USE_LIBUSB?=	No

MODULES+=		converters/libiconv
.if ${FLAVOUR:L:Mbig}
LIB_DEPENDS+=		bz2::archivers/bzip2
.endif
.if ${GPG_USE_LIBUSB:L} == "yes"
USE_CXX=		Yes
LIB_DEPENDS+=		usb::devel/libusb
.endif
B_R_DEPENDS+=		::archivers/mircpio
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
AUTOGEN=		${SHELL} ${WRKSRC:Q}/scripts/autogen.sh
CONFIGURE_ARGS+=	--enable-static-rnd=linux \
			--enable-rsa \
			--enable-idea \
			--enable-blowfish \
			--enable-aes \
			--enable-sha256 \
			--enable-sha512 \
			--disable-ldap \
			--disable-generic \
			--enable-mailto \
			--disable-nls \
			--enable-noexecstack \
			--without-included-zlib \
			--with-tar=${LOCALBASE:Q}/bin/tar \
			--without-libcurl \
			--without-included-regex

# libedit is *not* enough here.
CONFIGURE_ARGS+=	--without-readline

.if ${GPG_USE_LIBUSB:L} == "yes"
CONFIGURE_ARGS+=	--enable-card-support
.else
CONFIGURE_ARGS+=	--disable-card-support \
			--without-libusb
.endif

.if ${FLAVOUR:L:Mbig}
CONFIGURE_ARGS+=	--enable-bzip2
.else
CONFIGURE_ARGS+=	--disable-bzip2 \
			--without-bzip2
.endif

.if ${MACHINE_ARCH} != "i386"
CONFIGURE_ARGS+=	--disable-asm
.endif

.if ${MACHINE_OS} == "BSD"
# caught by systrace
CONFIGURE_ENV+=		gnupg_cv_ipc_rmid_deferred_release=no
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/gnupg
	cd ${WRKSRC:Q} && ${INSTALL_DATA} AUTHORS BUGS NEWS PROJECTS \
	    README THANKS TODO doc/DETAILS doc/HACKING doc/OpenPGP \
	    doc/highlights-1.4.txt doc/samplekeys.asc \
	    ${PREFIX:Q}/share/doc/gnupg/
	mv ${PREFIX:Q}/share/gnupg/FAQ ${PREFIX:Q}/share/doc/gnupg/

.include <bsd.port.mk>
