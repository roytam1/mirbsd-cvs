# $MirOS: ports/print/gentium-font/Makefile,v 1.5 2006/09/14 00:12:41 tg Exp $

COMMENT=		smart Unicode font families (Basic and Book Basic) based on Gentium
CATEGORIES=		print graphics textproc productivity x11
PKGSTEM=		ttf-sil-gentium-basic
VERSION=		1.1
DISTNAME=		${PKGSTEM}_${VERSION}.orig
PKGNAME=		${PKGSTEM}-${VERSION}-${DASH_VER}
HOMEPAGE=		http://scripts.sil.org/Gentium_basic
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# OFL (DFSG free)
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_DEBIAN:=t/${PKGSTEM}/}
WRKDIST=		${WRKDIR}/${PKGSTEM}-${VERSION}

FONTDIR=		${PREFIX}/lib/X11/fonts/${PKGSTEM}
USE_X11=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes

DOCS=			FONTLOG.txt GENTIUM-FAQ.txt OFL-FAQ.txt OFL.txt
FONTS=			GenBasB.ttf GenBasBI.ttf GenBasI.ttf GenBasR.ttf \
			GenBkBasB.ttf GenBkBasBI.ttf GenBkBasI.ttf GenBkBasR.ttf

do-install:
	@-rm -rf ${FONTDIR}
	${INSTALL_DATA_DIR} ${FONTDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${FONTS} ${FONTDIR}/
	cd ${FONTDIR} && \
	    ${X11BASE}/bin/mkfontscale . && \
	    ${X11BASE}/bin/mkfontdir .
	${X11BASE}/bin/fc-cache ${FONTDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${FONTDIR}/

.include <bsd.port.mk>
