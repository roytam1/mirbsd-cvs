# $MirOS: ports/emulators/wine/wine/Makefile,v 1.5 2005/10/11 20:58:58 tg Exp $
# $OpenBSD: Makefile,v 1.27 2003/05/12 22:19:11 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			MS-Windows 3.1/95/NT emulator for Unix (Alpha release)
DATE= 		990225
DISTNAME= 	Wine-${DATE}
PKGNAME=	wine-${DATE}-0
CATEGORIES=	emulators x11

# MIT/X11-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		yes
CONFIGURE_STYLE=	autoconf no-autoheader dest
WRKDIST=		${WRKDIR}/wine-${DATE}
NO_REGRESS=		Yes

post-configure:
	cd ${WRKSRC} && ${MAKE} depend

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/wine
	${INSTALL_DATA} ${WRKSRC}/wine.ini \
		${PREFIX}/share/examples/wine/wine.conf

.include <bsd.port.mk>
