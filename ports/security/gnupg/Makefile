# $MirOS$
# $OpenBSD: Makefile,v 1.42 2004/02/24 19:48:16 naddy Exp $

COMMENT=		"GNU privacy guard - a free PGP replacement"
VERSION=		1.2.4
DISTNAME=		gnupg-${VERSION}
CATEGORIES=		security
MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/gnupg/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/gnupg/ \
			ftp://crypto.yashy.com/pub/cryptography/gnupg/ \
			ftp://ftp.planetmirror.com/pub/gnupg/gnupg/ \
			ftp://sunsite.dk/pub/security/gcrypt/gnupg/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/gnupg/ \
			ftp://pgp.iijlab.net/pub/pgp/gnupg/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/gnupg/

MASTER_SITES0=		http://www.gnupg.dk/contrib-dk/ \
			ftp://ftp.gnupg.dk/pub/contrib-dk/
HOMEPAGE=		http://www.gnupg.org/
EXTRACT_SUFX=		.tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-ldap
CONFIGURE_ENV+=		CPPFLAGS="-I${LOCALBASE}/include" \
			LDFLAGS="-L${LOCALBASE}/lib"

FLAVORS=		idea
FLAVOR?=

.if ${FLAVOR:L:Midea}
PERMIT_PACKAGE_CDROM=	"patented algorithm"
PERMIT_DISTFILES_CDROM=	"patented algorithm"
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} idea.c.gz:0
.endif

post-extract:
.if ${FLAVOR:L:Midea}
	ln -s ${WRKDIR}/idea.c ${WRKSRC}/cipher/idea.c
.endif

GNUPGDOCFILES=	README AUTHORS COPYING THANKS TODO BUGS \
		doc/DETAILS doc/FAQ doc/OpenPGP doc/HACKING doc/faq.html

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gnupg
	cd ${WRKSRC}; ${INSTALL_DATA} ${GNUPGDOCFILES} \
		${PREFIX}/share/doc/gnupg

do-regress:
	@cd ${WRKSRC}/checks && ${MAKE_PROGRAM}

.include <bsd.port.mk>
