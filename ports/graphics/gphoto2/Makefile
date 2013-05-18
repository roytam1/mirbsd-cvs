# $MirOS: ports/graphics/gphoto2/Makefile,v 1.9 2006/09/14 00:09:54 tg Exp $
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

FLAVORS=		no_aa
FLAVOR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls

.if ${FLAVOR:Mno_aa}
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
