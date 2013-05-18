# $MirOS: ports/emulators/zsnes/Makefile,v 1.6 2005/10/03 22:23:40 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 15:06:49 fgsch Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Super Nintendo emulator for x86
VERSION=		1.42
DISTNAME=		zsnes-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=		emulators games
HOMEPAGE=		http://www.zsnes.com/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=zsnes/}
DISTFILES=		zsnes${VERSION:S/.//}src${EXTRACT_SUFX}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=		debug
FLAVOR?=

BUILD_DEPENDS=		nasm::lang/nasm
LIB_DEPENDS=		SDL.:sdl-*-!no_x11:devel/sdl \
			png.2::graphics/png

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

.if ${FLAVOR:L:Mdebug}
CONFIGURE_ARGS+=	--enable-debug
.endif

NO_REGRESS=		Yes

post-extract:
	rm -fr ${WRKSRC}/obj

post-install:
.if ${FLAVOR:L:Mdebug}
	rm -f ${PREFIX}/bin/zsnes
	mv ${PREFIX}/bin/zsnesd ${PREFIX}/bin/zsnes
.endif
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zsnes
	cd ${WRKDIST}/docs && \
	    find . -type f | cpio -pdlu ${PREFIX}/share/doc/zsnes/

.include <bsd.port.mk>
