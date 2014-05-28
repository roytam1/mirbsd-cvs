# $MirOS: ports/security/libgcrypt/Makefile,v 1.6 2008/08/26 18:59:17 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/05/08 06:41:47 sturm Exp $

COMMENT=		crypto library based on code used in GnuPG
DISTNAME=		libgcrypt-1.4.1
DASH_VER=		1
CATEGORIES=		security
HOMEPAGE=		http://directory.fsf.org/project/libgcrypt/

# GNU LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/libgcrypt/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/libgcrypt/ \
			http://ftp.planetmirror.com/pub/gnupg/libgcrypt/ \
			http://sunsite.dk/pub/security/gcrypt/libgcrypt/ \
			http://ftp.linux.it/pub/mirrors/gnupg/libgcrypt/

LIB_DEPENDS+=		gpg-error::security/libgpg-error

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-padlock-support \
			--disable-asm

post-extract:
	@rm -f ${WRKSRC}/doc/gcrypt.info

.include <bsd.port.mk>
