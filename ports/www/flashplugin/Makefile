# $MirOS: ports/www/flashplugin/Makefile,v 1.3 2005/04/11 15:57:04 tg Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Macromedia Flash Plugin for Linux Netscape and Opera
EMUL=		linux

VERSION=	5.0r51p1
DISTNAME=	flashplugin-${VERSION}
DISTFILES=	flash_linux.tar.gz
DIST_SUBDIR=	${DISTNAME}
CATEGORIES=     www
MASTER_SITES=	http://download.macromedia.com/pub/shockwave/flash/english/linux/${VERSION}/
HOMEPAGE=	http://www.macromedia.com/

# Restrictive
PERMIT_PACKAGE_CDROM=	"Redistribution not allowed"
PERMIT_PACKAGE_FTP=	"Redistribution not allowed"
PERMIT_DISTFILES_CDROM= "Redistribution not allowed"
PERMIT_DISTFILES_FTP=   "Redistribution not allowed"

IGNORE+=	"You can only use this port on a Personal Computer on"
IGNORE+=	"which Microsoft Windows, GNU/Linux, Sun Solaris, Apple"
IGNORE+=	"Mac OS or Mac OS X are installed. Furthermore, there are"
IGNORE+=	"additional restrictions shown at the licence page,"
IGNORE+=	"http://www.macromedia.com/shockwave/download/license/desktop/"
IGNORE+=	"Build this port with NO_IGNORE=Yes if you understood."

RUN_DEPENDS=    :redhat_base->=8.0:emulators/redhat/base

NO_BUILD=	Yes
NO_REGRESS=	Yes

WRKDIST=	${WRKDIR}/flash_linux

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/flash
	${INSTALL_DATA} ${WRKDIST}/libflashplayer.so \
			${WRKDIST}/ShockwaveFlash.class \
			${PREFIX}/lib/flash/

.include <bsd.port.mk>
