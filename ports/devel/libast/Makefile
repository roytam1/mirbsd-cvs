# $MirOS: ports/devel/libast/Makefile,v 1.1.7.1 2005/03/18 15:44:49 tg Exp $

COMMENT=			Library of Assorted Spiffy Things
VER=			0.5
DISTNAME=		libast-${VER}
CATEGORIES=		devel
MASTER_SITES=		http://www.eterm.org/download/
HOMEPAGE=		http://www.eterm.org/
RESPONSIBLE=		Jonathan Schleifer <js@h3c.de>

# similar to 4-clause BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		Imlib2.1::graphics/imlib2

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
