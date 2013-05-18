# $MirOS: ports/security/gnupg/Makefile,v 1.8 2006/09/11 01:02:03 tg Exp $
# $OpenBSD: Makefile,v 1.52 2005/05/17 15:08:34 martin Exp $

COMMENT=		GNU privacy guard - a GPL'd PGP replacement
VERSION=		1.4.5
DISTNAME=		gnupg-${VERSION}
PKGNAME=		${DISTNAME}-2
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
LIB_DEPENDS+=		curl::net/curl
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
AUTOGEN=		${SHELL} ${WRKSRC}/scripts/autogen.sh
CONFIGURE_ARGS+=	--disable-ldap
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--enable-noexecstack
CONFIGURE_ARGS+=	--disable-nls
.if ${MACHINE_ARCH} == "m68k"
CONFIGURE_ARGS+=	--disable-asm
.endif

FLAVORS=		idea card
FLAVOR?=

.if ${FLAVOR:L:Midea}
PERMIT_DISTFILES_CDROM=	http://www.mediacrypt.com/engl/Content/licensing_policy.htm
PERMIT_PACKAGE_CDROM=	"patented algorithm"
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} idea.c.gz:0
CONFIGURE_ARGS+=	--enable-idea
.else
SUPDISTFILES=		idea.c.gz:0
CONFIGURE_ARGS+=	--disable-idea
.endif

.if ${FLAVOR:L:Mcard}
LIB_DEPENDS+=		usb::devel/libusb
.else
CONFIGURE_ARGS+=	--disable-card-support --without-libusb
.endif

post-extract:
.if ${FLAVOR:L:Midea}
	ln -s ${WRKDIR}/idea.c ${WRKSRC}/cipher/idea.c
.endif

DOCFILES=	README AUTHORS COPYING THANKS TODO BUGS \
		doc/DETAILS doc/FAQ doc/OpenPGP doc/HACKING doc/faq.html

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gnupg
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCFILES} ${PREFIX}/share/doc/gnupg/

.include <bsd.port.mk>
