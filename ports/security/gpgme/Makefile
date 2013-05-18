# $MirOS: ports/security/gpgme/Makefile,v 1.2 2006/09/13 20:54:59 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/05/27 14:16:48 couderc Exp $

COMMENT=			GnuPG Made Easy
DISTNAME=		gpgme-1.0.3
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

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--without-gpgsm \
			--without-pth \
			--disable-dependency-tracking \
			--disable-libtool-lock
CONFIGURE_ENV+=		MAKEINFO="makeinfo --no-split"

BUILD_DEPENDS=		:gnupg->=1.2.2:security/gnupg
RUN_DEPENDS=		${BUILD_DEPENDS}
LIB_DEPENDS+=		gpg-error::security/libgpg-error

post-extract:
	@rm -f ${WRKSRC}/doc/gpgme.info*

.include <bsd.port.mk>
