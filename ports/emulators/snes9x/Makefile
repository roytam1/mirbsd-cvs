# $MirOS: ports/emulators/snes9x/Makefile,v 1.6 2008/10/05 01:23:45 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/04/10 18:08:56 jsyn Exp $

ONLY_FOR_PLATFORM=	*BSD:*:i386
EMUL=			linux

COMMENT=		emulates the Super Nintendo Entertainment System
VERSION=		1.51
PKGNAME=		snes9x-${VERSION}-${DASH_VER}
DISTNAME=		snes9x-${VERSION}-linux-x86
CATEGORIES=		emulators games
HOMEPAGE=		http://www.snes9x.com/

# personal use
PERMIT_DISTFILES_CDROM=	non-commercial freeware
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	non-commercial freeware
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.lysator.liu.se/snes9x/${VERSION}/ \
			http://files.ipherswipsite.com/snes9x/ \
			http://www.geocities.co.jp/SiliconValley-PaloAlto/2560/release/ \
			http://www.geocities.co.jp/SiliconValley-PaloAlto/2560/release/old/

RUN_DEPENDS+=		::emulators/fedora

USE_X11=		Yes
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}/snes9x-${VERSION}

do-build:
	print ',g//s//\\\n/g\nwq' | ed -s ${WRKSRC}/snes9x-license.txt

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/snes9x
	${INSTALL_DATA} ${WRKSRC}/*.txt ${WRKSRC}/snes9x.conf.default \
	    ${PREFIX}/share/doc/snes9x/
	${INSTALL_SCRIPT} ${WRKSRC}/snes9x ${PREFIX}/bin/

.include <bsd.port.mk>
