# $MirOS: ports/devel/t1lib/Makefile,v 1.4 2007/02/22 20:58:59 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/04/14 18:26:38 brad Exp $

COMMENT=		Type 1 rasterizer library for UNIX/X11
DISTNAME=		t1lib-5.1.1
CATEGORIES=		devel graphics
MASTER_SITES=		ftp://sunsite.unc.edu/pub/Linux/libs/graphics/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
USE_X11=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
ALL_TARGET=		without_doc
NO_REGRESS=		Yes

.include <bsd.port.mk>
