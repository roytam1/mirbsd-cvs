# $MirOS: ports/net/cadaver/Makefile,v 1.2 2006/06/03 16:02:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/05/19 18:04:37 lebel Exp $

COMMENT=			command-line WebDAV client

VERSION=		0.22.2
DISTNAME=		cadaver-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=     	net www

HOMEPAGE=		http://www.webdav.org/cadaver/


LIB_DEPENDS=		xml2.2.6:libxml->=2.4.8:textproc/libxml
MODULES=		converters/libiconv

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

NO_REGRESS=		Yes
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ARGS=		--with-ssl --with-xml2 --with-included-neon

.include <bsd.port.mk>
