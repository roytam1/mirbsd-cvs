# $MirOS: ports/security/opencdk/Makefile,v 1.1.7.1 2005/03/18 15:51:37 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/05/08 06:42:59 sturm Exp $

COMMENT=			Open Crypto Development Kit
VERSION=		0.5.5
DISTNAME=		opencdk-${VERSION}
EXTRACT_SUFX=		.tar.bz2
CATEGORIES=		security
RESPONSIBLE=		Jonathan Schleifer <js@h3c.de>
HOMEPAGE=		http://www.gnutls.org/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.gnutls.org/pub/gnutls/opencdk/ \
		ftp://ftp.gnupg.org/gcrypt/alpha/gnutls/opencdk/ \
		ftp://gd.tuwien.ac.at/privacy/gnupg/alpha/gnutls/opencdk/ \
		http://sunsite.dk/pub/security/gcrypt/alpha/gnutls/opencdk/ \
		http://ftp.linux.it/pub/mirrors/gnupg/alpha/gnutls/opencdk/

LIB_DEPENDS=	gcrypt.12::security/libgcrypt

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=${CONFIGURE_SHARED} \
		--enable-static \
		--with-libgcrypt-prefix=${LOCALBASE}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/opencdk
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/opencdk
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/opencdk
	${INSTALL_DATA} ${WRKSRC}/doc/opencdk-api.html \
		${PREFIX}/share/doc/opencdk
	${INSTALL_DATA} ${WRKSRC}/tests/*.c \
		${PREFIX}/share/examples/opencdk
	${INSTALL_DATA} ${WRKSRC}/tests/*.gpg \
		${PREFIX}/share/examples/opencdk

.include <bsd.port.mk>
