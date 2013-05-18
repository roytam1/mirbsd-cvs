# $MirOS: ports/security/libotr/Makefile,v 1.1 2008/04/03 21:28:14 tg Exp $
# $OpenBSD: Makefile,v 1.9 2007/11/29 14:05:48 okan Exp $
# $FreeBSD: Makefile,v 1.2 2005/04/21 14:22:54 pav Exp $

COMMENT=		portable OTR Messaging Library and toolkit
DISTNAME=		libotr-3.2.0
CATEGORIES=		security
HOMEPAGE=		http://www.cypherpunks.ca/otr/
MASTER_SITES=		${HOMEPAGE}

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		gpg-error::security/libgpg-error \
			gcrypt::security/libgcrypt

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libotr
	cd ${WRKSRC} && ${INSTALL_DATA} AUTHORS NEWS Protocol-v2.html \
	    README UPGRADING ${PREFIX}/share/doc/libotr/

.include <bsd.port.mk>
