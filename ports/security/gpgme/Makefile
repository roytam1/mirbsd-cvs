# $MirOS: ports/security/gpgme/Makefile,v 1.8 2007/03/20 18:28:25 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/05/27 14:16:48 couderc Exp $

COMMENT=		GnuPG Made Easy
DISTNAME=		gpgme-1.1.4
CATEGORIES=     	security devel
HOMEPAGE=		http://www.gnupg.org/related_software/gpgme/

# GPL
PERMIT_PACKAGE_CDROM=	dependency security/gnupg is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/gpgme/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/gpgme/ \
			ftp://sunsite.dk/pub/security/gcrypt/gpgme/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/gpgme/ \
			ftp://pgp.iijlab.net/pub/pgp/gpgme/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/gpgme/

USE_CXX=		Yes # depends on libusb, which uses CXX
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-fd-passing \
			--disable-glib2 \
			--without-gpgsm \
			--without-pth
# disable pthread
CONFIGURE_ENV+=		ac_cv_lib_pthread_pthread_create=no

B_R_DEPENDS+=		:gnupg->=1.3.0:security/gnupg
LIB_DEPENDS+=		gpg-error:libgpg-error->=1.4:security/libgpg-error

post-extract:
	@rm -f ${WRKSRC}/doc/gpgme.info*

.include <bsd.port.mk>
