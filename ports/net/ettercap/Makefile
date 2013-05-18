# $MirOS: ports/net/ettercap/Makefile,v 1.4 2006/02/09 11:12:14 tg Exp $
# $OpenBSD: Makefile,v 1.26 2004/02/25 02:35:16 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			multi-purpose sniffer/interceptor/logger

VER=		0.6.b
DISTNAME=	ettercap-${VER}
CATEGORIES=	net

HOMEPAGE=	http://ettercap.sourceforge.net/

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ettercap/} \
		${MASTER_SITE_PACKETSTORM:=sniffers/ettercap/}


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

FLAVORS=		no_x11
FLAVOR?=

MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-https

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--enable-gtk=no
.else
USE_CXX=	Yes
USE_X11=	Yes
LIB_DEPENDS=	gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
.endif

NO_REGRESS=	Yes

.include <bsd.port.mk>
