# $MirOS: ports/graphics/libcaca/Makefile,v 1.4 2006/09/14 00:09:57 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/04/18 06:41:11 robert Exp $

COMMENT=			colour ascii art library
DISTNAME=		libcaca-0.9
PKGNAME=		${DISTNAME}-2
CATEGORIES=		graphics
HOMEPAGE=		http://sam.zoy.org/libcaca/
MASTER_SITES=		${HOMEPAGE}

# GNU LGPLv2.1
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=    	Imlib2.1::graphics/imlib2,no_cxx

FLAVOURS=		no_x11
FLAVOUR?=

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--disable-x11
.else
USE_X11=		Yes
.endif

CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-doc --disable-slang

.include <bsd.port.mk>
