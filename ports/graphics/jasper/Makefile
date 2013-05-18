# $MirOS: ports/graphics/jasper/Makefile,v 1.3 2005/07/07 21:21:43 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/14 05:33:57 brad Exp $

COMMENT=			software-based reference implementation of the JPEG-2000 codec

DISTNAME=	jasper-1.701.0
PKGNAME=	${DISTNAME}-0
CATEGORIES=	graphics
MASTER_SITES=	${HOMEPAGE}software/
EXTRACT_SUFX=	.zip

HOMEPAGE=	http://www.ece.uvic.ca/~mdadams/jasper/


# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	 Yes
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --without-x --disable-opengl

.include <bsd.port.mk>
