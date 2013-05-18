# $MirOS: ports/security/mcrypt/Makefile,v 1.2 2006/02/09 11:15:20 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/04/10 18:08:57 jsyn Exp $

COMMENT=			extendable encryption program that supports many ciphers
DISTNAME=		mcrypt-2.6.3
CATEGORIES=     	security
HOMEPAGE=		http://mcrypt.hellug.gr/mcrypt/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://argeas.cs-net.gr/pub/unix/mcrypt/ \
			ftp://mcrypt.hellug.gr/pub/mcrypt/ 

USE_GMAKE=		Yes
#MODULES=		gettext
LIB_DEPENDS=		mcrypt.6::security/libmcrypt

CONFIGURE_STYLE=	autoconf automake
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 	--enable-static --with-catgets 
LDFLAGS+=		-lintl

.include <bsd.port.mk>
