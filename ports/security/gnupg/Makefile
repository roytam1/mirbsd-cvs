# $MirOS: ports/security/gnupg/Makefile,v 1.11 2006/10/02 02:05:44 tg Exp $
# $OpenBSD: Makefile,v 1.52 2005/05/17 15:08:34 martin Exp $

COMMENT=		GNU privacy guard - a GPL'd PGP replacement
VERSION=		1.4.5
DISTNAME=		gnupg-${VERSION}
PKGNAME=		${DISTNAME}-4
CATEGORIES=		security
HOMEPAGE=		http://www.gnupg.org/
MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/gnupg/ \
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
BUILD_DEPENDS+=		::archivers/mircpio
RUN_DEPENDS+=		::archivers/mircpio
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
AUTOGEN=		${SHELL} ${WRKSRC}/scripts/autogen.sh
CONFIGURE_ARGS+=	--enable-static-rnd=linux \
			--disable-ldap \
			--disable-generic \
			--disable-dependency-tracking \
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

FLAVORS=		no-idea

.include <mirports.sys.mk>

.if ${MKC_USAP:L} == "yes"
FLAVOR?=		no-idea
.else
FLAVOR?=
.endif

.if ${FLAVOR:L:Mno-idea}
SUPDISTFILES=		idea.c.gz:0
CONFIGURE_ARGS+=	--disable-idea
.else
PERMIT_PACKAGE_CDROM=	http://www.mediacrypt.com/engl/Content/licensing_policy.htm
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} idea.c.gz:0
CONFIGURE_ARGS+=	--enable-idea
.endif

post-extract:
	@rm -f ${WRKSRC}/cipher/idea.c
.if !${FLAVOR:L:Mno-idea}
	ln -s ${WRKDIR}/idea.c ${WRKSRC}/cipher/idea.c
.endif

DOCFILES=	README AUTHORS COPYING THANKS TODO BUGS \
		doc/DETAILS doc/FAQ doc/OpenPGP doc/HACKING doc/faq.html

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gnupg
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCFILES} ${PREFIX}/share/doc/gnupg/

.include <bsd.port.mk>
