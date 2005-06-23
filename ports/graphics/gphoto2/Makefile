# $MirOS: ports/graphics/gphoto2/Makefile,v 1.2 2005/06/23 13:52:33 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/04/14 18:41:15 brad Exp $

COMMENT=	'digital camera command-line interface'
CATEGORIES=	graphics
VERSION=	2.1.4
DISTNAME=	gphoto2-${VERSION}
PKGNAME=	gphoto-${VERSION}-0
HOMEPAGE=	http://gphoto.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gphoto/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
SEPARATE_BUILD=		simple
CONFIGURE_ARGS=		--disable-nls --without-aalib --without-cdk

LIB_DEPENDS+=	gphoto2,gphoto2_port::graphics/libgphoto2 \
		jpeg::graphics/jpeg \
		popt::devel/popt

.include <bsd.port.mk>
