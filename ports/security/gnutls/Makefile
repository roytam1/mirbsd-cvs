# $MirOS: ports/security/gnutls/Makefile,v 1.2 2006/09/14 00:12:59 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/05/08 06:43:40 sturm Exp $

BROKEN=			insecure, not updated for too long a time

COMMENT=			GNU Transport Layer Security library
VERSION=		1.0.20
DISTNAME=		gnutls-${VERSION}
CATEGORIES=		security
RESPONSIBLE=		Jonathan Schleifer <js@h3c.de>
HOMEPAGE=		http://www.gnutls.org/

# GNU LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.gnupg.org/gcrypt/gnutls/ \
		ftp://gd.tuwien.ac.at/privacy/gnupg/gnutls/ \
		http://sunsite.dk/pub/security/gcrypt/gnutls/ \
		http://ftp.linux.it/pub/mirrors/gnupg/gnutls/

LIB_DEPENDS=	gcrypt.12::security/libgcrypt \
		opencdk.8.1::security/opencdk \
		lzo::archivers/lzo

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-included-libtasn1 \
			--with-included-libcfg

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/gnutls

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gnutls
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gnutls
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/gnutls
	${INSTALL_DATA} ${WRKSRC}/doc/examples/*.c \
	    ${PREFIX}/share/examples/gnutls

.include <bsd.port.mk>
