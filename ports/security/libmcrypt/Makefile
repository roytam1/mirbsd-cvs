# $MirOS: ports/security/libmcrypt/Makefile,v 1.1.7.1 2005/03/18 15:51:30 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/01/18 22:53:29 avsm Exp $

COMMENT=			interface to access block/stream encryption algorithms
DISTNAME=	libmcrypt-2.5.5
CATEGORIES=	security
MASTER_SITES=	ftp://mcrypt.hellug.gr/pub/mcrypt/libmcrypt/ \
		ftp://argeas.cs-net.gr/pub/unix/mcrypt/libmcrypt/
HOMEPAGE=	http://mcrypt.hellug.gr/lib/

LIB_DEPENDS=	mhash.2::security/mhash

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

.include <bsd.port.mk>
