# $MirOS: ports/audio/libao/Makefile,v 1.5 2006/02/09 09:35:36 tg Exp $
# $OpenBSD: Makefile,v 1.23 2003/10/08 16:01:45 naddy Exp $

COMMENT=		"portable audio output library"
COMMENT-arts=		"aRts module for portable audio output library"
COMMENT-esd=		"ESounD module for portable audio output library"

VERSION=		0.8.6
DISTNAME=		libao-${VERSION}
PL=			1
PKGNAME=		${DISTNAME}-${PL}
PKGNAME-arts=		libao-arts-${VERSION}-${PL}
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

PSEUDO_FLAVORS=		no_arts no_esd
FLAVOR?=		no_arts

MULTI_PACKAGES=
.if !${FLAVOR:L:Mno_arts}
MULTI_PACKAGES+=	-arts
.endif
.if !${FLAVOR:L:Mno_esd}
MULTI_PACKAGES+=	-esd
.endif

SUBPACKAGE?=

CONFIGURE_STYLE=	autogen no-autoheader
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-static
.if ${FLAVOR:L:Mno_arts}
CONFIGURE_ARGS+=	--disable-arts
.endif
.if ${FLAVOR:L:Mno_esd}
CONFIGURE_ARGS+=	--disable-esd
.endif
CONFIGURE_ARGS+=	--disable-nas

.if defined(PACKAGING)
.  if ${SUBPACKAGE} == "-arts"
LIB_DEPENDS=		ao::audio/libao \
			artsc::x11/kde/arts3
.  elif ${SUBPACKAGE} == "-esd"
LIB_DEPENDS=		ao::audio/libao \
			esd::audio/esound
.  endif
.else
.  if !${FLAVOR:L:Mno_arts}
LIB_DEPENDS+=		artsc::x11/kde/arts3
.  endif
.  if !${FLAVOR:L:Mno_esd}
LIB_DEPENDS+=		esd::audio/esound
.  endif
.endif

.include <bsd.port.mk>
