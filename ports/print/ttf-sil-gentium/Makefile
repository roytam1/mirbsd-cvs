# $MirOS: ports/print/ttf-sil-gentium/Makefile,v 1.2 2009/06/22 12:07:31 tg Exp $

COMMENT=		extended Unicode Latin font ("a typeface for the nations")
CATEGORIES=		print graphics textproc productivity x11
PKGSTEM=		ttf-sil-gentium
VERSION=		1.02
DASH_VER=		1
DISTNAME=		${PKGSTEM}_${VERSION}.orig
PKGNAME=		${PKGSTEM}-${VERSION}-${DASH_VER}
HOMEPAGE=		http://scripts.sil.org/Gentium
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# OFL (DFSG free)
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_DEBIAN:=t/${PKGSTEM}/}
WRKDIST=		${WRKDIR}/${PKGSTEM}-${VERSION}

FONTDIR=		${PREFIX}/lib/X11/fonts/${PKGSTEM}
VSN=			${VERSION:S/.//}
USE_X11=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes

DOCS=			FONTLOG GENTIUM-FAQ OFL OFL-FAQ QUOTES README
FONTS=			GenAI${VSN}.ttf GenAR${VSN}.ttf GenI${VSN}.ttf GenR${VSN}.ttf

do-install:
	@-rm -rf ${FONTDIR}
	${INSTALL_DATA_DIR} ${FONTDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${FONTS} ${FONTDIR}/
	cd ${FONTDIR} && \
	    ${X11BASE}/bin/mkfontscale . && \
	    ${X11BASE}/bin/mkfontdir .
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${FONTDIR}/

.include <bsd.port.mk>
