# $MirOS: ports/www/snownews/Makefile,v 1.3 2006/09/14 00:14:58 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/01/25 05:49:35 jolan Exp $

COMMENT=		text mode RSS newsreader
VERSION=                1.4.4
DASH_VER=		1
DISTNAME=		snownews-${VERSION}
CATEGORIES=		www
HOMEPAGE=		http://home.kcore.de/~kiza/software/snownews/
MASTER_SITES=		${HOMEPAGE}download/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=        	devel/gettext
LIB_DEPENDS+=		xml2::textproc/libxml
USE_GMAKE=		Yes
NO_REGRESS=     	Yes
MAKE_ENV+=		EXTRA_LDFLAGS="-lintl -liconv" INSTALL=install

.include <bsd.port.mk>
