# $MirOS: ports/emulators/zsnes/Makefile,v 1.9 2008/10/30 19:42:06 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 15:06:49 fgsch Exp $

ONLY_FOR_PLATFORM=	*BSD:*:i386

COMMENT=		Super Nintendo emulator for x86
VERSION=		1.42
DASH_VER=		2
DISTNAME=		zsnes-${VERSION}
CATEGORIES=		emulators games
HOMEPAGE=		http://www.zsnes.com/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=zsnes/}
DISTFILES=		zsnes${VERSION:S/.//}src${EXTRACT_SUFX}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		debug
FLAVOUR?=

BUILD_DEPENDS=		nasm::lang/nasm
LIB_DEPENDS=		SDL.:sdl-*-!no_x11:devel/sdl
MODULES+=		graphics/png

USE_X11=		Yes
USE_CXX=		Yes

WRKDIST=		${WRKDIR}/zsnes_${VERSION:S/./_/}
WRKSRC=			${WRKDIST}/src

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--with-sdl-prefix=${LOCALBASE} \
			--with-opengl \
			--with-png
ALL_TARGET=		ALL
CPPFLAGS+=		-D__GZIP__

.if ${FLAVOUR:L:Mdebug}
CONFIGURE_ARGS+=	--enable-debug
.endif

NO_REGRESS=		Yes

post-extract:
	rm -fr ${WRKSRC}/obj
	cp ${.CURDIR}/zsnes.1 ${WRKSRC}/linux/

post-install:
.if ${FLAVOUR:L:Mdebug}
	rm -f ${PREFIX}/bin/zsnes
	mv ${PREFIX}/bin/zsnesd ${PREFIX}/bin/zsnes
.endif
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zsnes
	cd ${WRKDIST}/docs && pax -rw . ${PREFIX}/share/doc/zsnes/

.include <bsd.port.mk>
