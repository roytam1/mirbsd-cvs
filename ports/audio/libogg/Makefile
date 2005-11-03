# $MirOS: ports/audio/libogg/Makefile,v 1.1.7.1 2005/03/18 15:42:57 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/12/14 00:52:21 naddy Exp $

COMMENT=	"Ogg bitstream library"
DISTNAME=	libogg-1.1.2
CATEGORIES=    	audio
HOMEPAGE=	http://www.xiph.org/ogg/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://downloads.xiph.org/releases/ogg/

BUILD_DEPENDS=	pkgconfig-*::devel/pkgconfig

CONFIGURE_STYLE=autogen
AUTOCONF_NEW=	Yes
AUTOMAKE_VERSION= 1.9
CONFIGURE_ARGS=	${CONFIGURE_SHARED}
SEPARATE_BUILD=	simple

.include <bsd.port.mk>
