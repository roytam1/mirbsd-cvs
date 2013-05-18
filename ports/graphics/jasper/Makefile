# $MirOS: ports/graphics/jasper/Makefile,v 1.4 2006/09/14 00:09:56 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/14 05:33:57 brad Exp $

COMMENT=		software-based reference implementation of the JPEG-2000 codec

DISTNAME=		jasper-1.900.1
DASH_VER=		0
CATEGORIES=		graphics
EXTRACT_SUFX=		.zip

HOMEPAGE=		http://www.ece.uvic.ca/~mdadams/jasper/
MASTER_SITES=		${HOMEPAGE}software/


# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--without-x --disable-opengl

.include <bsd.port.mk>
