# $MirOS: ports/graphics/gphoto2/Makefile,v 1.7 2005/12/30 01:47:45 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/04/14 18:41:15 brad Exp $

COMMENT=		'digital camera command-line interface'
CATEGORIES=		graphics
VERSION=		2.1.6
DISTNAME=		gphoto2-${VERSION}
PKGNAME=		gphoto-${VERSION}-0
HOMEPAGE=		http://gphoto.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gphoto/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls \
			--with-aalib

.include <mirports.sys.mk>
.if ${OStype} == "MirBSD"
CONFIGURE_ARGS+=	--with-cdk
.else
CONFIGURE_ARGS+=	--without-cdk
.endif

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		gphoto2,gphoto2_port::graphics/libgphoto2 \
			aa::graphics/aalib \
			jpeg::graphics/jpeg \
			popt::devel/popt

.include <bsd.port.mk>
