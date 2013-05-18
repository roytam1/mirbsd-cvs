# $MirOS: ports/audio/libogg/Makefile,v 1.6 2006/11/03 23:14:14 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/12/14 00:52:21 naddy Exp $

COMMENT=		Ogg bitstream (container file format) library
DISTNAME=		libogg-1.1.3
CATEGORIES=    		audio
HOMEPAGE=		http://www.xiph.org/ogg/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/ogg/
MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static

.include <bsd.port.mk>
