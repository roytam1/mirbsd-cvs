# $MirOS: ports/textproc/libxml1/Makefile,v 1.3 2005/10/24 21:57:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2003/11/15 15:12:53 sturm Exp $

COMMENT=			XML parsing library for GNOME

VERSION=	1.8.17
DISTNAME=	libxml-${VERSION}
PKGNAME=	libxml1-${VERSION}-1
CATEGORIES=	textproc
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/libxml/1.8/}

HOMEPAGE=	http://xmlsoft.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--with-html-dir="${PREFIX}/share"

.include <bsd.port.mk>
