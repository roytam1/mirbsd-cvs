# $MirOS: ports/audio/libmikmod/Makefile,v 1.6 2008/03/09 17:22:24 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/01/24 19:57:34 pvalchev Exp $

COMMENT=		mikmod sound library
VERSION=		3.1.10
DISTNAME=		libmikmod-${VERSION}
DASH_VER=		5
CATEGORIES=    		audio devel
HOMEPAGE=		http://mikmod.raphnet.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/files/libmikmod/ \
			${MASTER_SITE_SUNSITE:=apps/sound/libs/}

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-dl \
			--enable-oss

FLAVOURS=		esd
FLAVOUR?=

.if ${FLAVOUR:L:Mesd}
CONFIGURE_ARGS+=	--enable-esd
LIB_DEPENDS+=		esd.2::audio/esound
.else
CONFIGURE_ARGS+=	--disable-esd
.endif

.include <bsd.port.mk>
