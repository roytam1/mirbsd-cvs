# $MirOS: ports/audio/libao/Makefile,v 1.10 2007/04/03 19:41:55 tg Exp $
# $OpenBSD: Makefile,v 1.23 2003/10/08 16:01:45 naddy Exp $

COMMENT=		portable audio output library
COMMENT-esd=		ESounD module for portable audio output library

VERSION=		0.8.6
DISTNAME=		libao-${VERSION}
PL=			2
PKGNAME=		${DISTNAME}-${PL}
PKGNAME-esd=		libao-esd-${VERSION}-${PL}
CATEGORIES=    		audio
HOMEPAGE=		http://www.xiph.org/ao/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/ao/

USE_CXX=		Yes
MODULES+=		devel/pkgconfig

PSEUDO_FLAVOURS=		no_esd
FLAVOUR?=

MULTI_PACKAGES=
.if !${FLAVOUR:L:Mno_esd}
MULTI_PACKAGES+=	-esd
.endif

SUBPACKAGE?=

CONFIGURE_STYLE=	autogen no-autoheader
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-static
CONFIGURE_ARGS+=	--disable-arts
.if ${FLAVOUR:L:Mno_esd}
CONFIGURE_ARGS+=	--disable-esd
.endif
CONFIGURE_ARGS+=	--disable-nas

.if defined(PACKAGING) && (${SUBPACKAGE} == "-esd")
LIB_DEPENDS+=		ao::audio/libao \
			esd::audio/esound
.else
.  if !${FLAVOUR:L:Mno_esd}
LIB_DEPENDS+=		esd::audio/esound
.  endif
.endif

.include <bsd.port.mk>
