# $MirOS: ports/multimedia/livestream/Makefile,v 1.9 2009/08/16 16:27:35 tg Exp $

COMMENT=			library for live.com streaming servers
VSN=			2005.12.23
DISTNAME=		live.${VSN}
PKGNAME=		liblivestream-${VSN}-${DASH_VER}
CATEGORIES=		graphics net multimedia
MASTER_SITES=		http://www.live555.com/liveMedia/public/
HOMEPAGE=		http://www.live555.com/liveMedia/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU LGPL v2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
WRKDIST=		${WRKDIR}/live
MAKE_FILE=		${FILESDIR}/BSDmakefile
MAKE_FLAGS+=		WRKSRC="${WRKSRC}" CC=${_PASS_CC:T:Q} CXX=${_PASS_CXX:T:Q} \
			COPTS="${COPTS}" LD="${LD}"
FAKE_FLAGS+=		WRKSRC="${WRKSRC:C/${PREFIX}/${TRUEPREFIX}/}"

do-configure:
	${MAKE} ${MAKE_FLAGS} -f ${MAKE_FILE} configure

.include <bsd.port.mk>
