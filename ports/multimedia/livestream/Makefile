# $MirOS: ports/multimedia/livestream/Makefile,v 1.4 2005/07/07 21:23:56 bsiegert Exp $

COMMENT=		"library for live.com streaming servers"
V=			2005.05.12
DISTNAME=		live.$V
PKGNAME=		liblivestream-$V-0
CATEGORIES=		graphics net multimedia
MASTER_SITES=		http://www.live.com/liveMedia/public/
HOMEPAGE=		http://www.live.com/liveMedia/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU LGPL v2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
WRKDIST=		${WRKDIR}/live
MAKE_FILE=		${FILESDIR}/BSDmakefile
MAKE_FLAGS+=		WRKSRC="${WRKSRC}" CC="${CC}" CXX="${CXX}" \
			COPTS="${COPTS}" LD="${LD}"
FAKE_FLAGS+=		WRKSRC="${WRKSRC:C/${PREFIX}/${TRUEPREFIX}/}"

do-configure:
	${MAKE} ${MAKE_FLAGS} -f ${MAKE_FILE} configure

.include <bsd.port.mk>
