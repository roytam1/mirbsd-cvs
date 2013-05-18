# $MirOS: ports/audio/id3lib/Makefile,v 1.3 2007/03/21 20:05:34 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/01/10 03:15:19 brad Exp $

COMMENT=		library for manipulating ID3v1 and ID3v2 tags

VERSION=		3.8
DISTNAME=		id3lib-${VERSION}.3
DASH_VER=		1
CATEGORIES=     	audio
HOMEPAGE=		http://id3lib.sourceforge.net/
USE_CXX=		Yes

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=id3lib/}

USE_GMAKE=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

.include <bsd.port.mk>
