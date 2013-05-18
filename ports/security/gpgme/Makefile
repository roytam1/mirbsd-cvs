# $MirOS: ports/security/gpgme/Makefile,v 1.5 2006/11/16 22:12:09 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/05/27 14:16:48 couderc Exp $

COMMENT=		GnuPG Made Easy
DISTNAME=		gpgme-1.0.3
PKGNAME=		${DISTNAME}-2
CATEGORIES=     	security devel
HOMEPAGE=		http://www.gnupg.org/gpgme.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/gpgme/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/gpgme/ \
			ftp://sunsite.dk/pub/security/gcrypt/gpgme/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/gpgme/ \
			ftp://pgp.iijlab.net/pub/pgp/gpgme/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/gpgme/

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--without-gpgsm \
			--without-pth \
			--disable-dependency-tracking \
			--disable-libtool-lock
CONFIGURE_ENV+=		MAKEINFO="makeinfo --no-split"
# disable pthread
CONFIGURE_ENV+=		ac_cv_lib_pthread_pthread_create=no

B_R_DEPENDS+=		:gnupg->=1.2.2:security/gnupg
LIB_DEPENDS+=		gpg-error::security/libgpg-error

post-extract:
	@rm -f ${WRKSRC}/doc/gpgme.info*

.include <bsd.port.mk>
