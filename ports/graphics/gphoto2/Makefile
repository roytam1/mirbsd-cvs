# $MirOS: ports/graphics/gphoto2/Makefile,v 1.10 2007/01/08 18:00:51 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/04/14 18:41:15 brad Exp $

COMMENT=		digital camera command-line interface
CATEGORIES=		graphics
VERSION=		2.1.6
DASH_VER=		1
DISTNAME=		gphoto2-${VERSION}
PKGNAME=		gphoto-${VERSION}-${DASH_VER}
HOMEPAGE=		http://gphoto.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gphoto/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

FLAVOURS=		no_aa
FLAVOUR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls

.if ${FLAVOUR:Mno_aa}
CONFIGURE_ARGS+=	--without-aalib
.else
CONFIGURE_ARGS+=	--with-aalib
LIB_DEPENDS+=		aa::graphics/aalib
.endif

.if exists(/usr/lib/libcdk.a)
CONFIGURE_ARGS+=	--with-cdk
.else
CONFIGURE_ARGS+=	--without-cdk
.endif

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		gphoto2,gphoto2_port::graphics/libgphoto2 \
			jpeg::graphics/jpeg \
			popt::devel/popt

.include <bsd.port.mk>
