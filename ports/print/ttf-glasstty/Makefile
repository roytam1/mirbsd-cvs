# $MirOS$

COMMENT=		Truetype font mimicking DEC VT220
CATEGORIES=		print textproc x11
PKGSTEM=		ttf-glasstty
VSN=			20091031
DIST_SUBDIR=		${PKGSTEM}-${VSN}
DISTNAME=		Glass_TTY_VT220
EXTRACT_SUFX=		.ttf
EXTRACT_ONLY=
WRKDIST=		${WRKDIR}
PKGNAME=		${PKGSTEM}-${VSN}-${DASH_VER}
HOMEPAGE=		http://sensi.org/~svo/glasstty/

# apparently freely redistributable
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}
FONTDIR=		${PREFIX}/lib/X11/fonts/${PKGSTEM}
USE_X11=		Yes
NO_EXTRACT=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	@-rm -rf ${FONTDIR}
	${INSTALL_DATA_DIR} ${FONTDIR}
	cd ${FULLDISTDIR} && ${INSTALL_DATA} ${DISTFILES} ${FONTDIR}/
	cd ${FONTDIR} && \
	    ${X11BASE}/bin/mkfontscale . && \
	    ${X11BASE}/bin/mkfontdir .

.include <bsd.port.mk>
