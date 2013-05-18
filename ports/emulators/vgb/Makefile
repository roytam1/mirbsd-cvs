# $MirOS: ports/emulators/vgb/Makefile,v 1.6 2008/10/05 01:23:46 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/04/10 18:08:56 jsyn Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		Emulator for the Nintendo Gameboy
PKGNAME=		vgb-2.1-2
DISTNAME=		VGB21-Linux-80x86-bin
CATEGORIES=		emulators games
HOMEPAGE=		http://www.komkon.org/fms/VGB/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}
EXTRACT_SUFX=		.tar.Z

RUN_DEPENDS+=		::emulators/fedora

USE_X11=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/vgb
	${INSTALL_PROGRAM} ${WRKSRC}/vgb ${PREFIX}/bin/
	${INSTALL_DATA} ${WRKSRC}/{CART.GB,VGB.html} ${PREFIX}/share/doc/vgb/

.include <bsd.port.mk>
