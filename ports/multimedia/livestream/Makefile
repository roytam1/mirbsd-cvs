# $MirOS: ports/multimedia/livestream/Makefile,v 1.1.7.1 2005/03/18 15:50:47 tg Exp $

COMMENT=		"library for live.com streaming servers"
V=			2005.04.26
DISTNAME=		live.$V
PKGNAME=		liblivestream-$V
CATEGORIES=		graphics net multimedia
MASTER_SITES=		http://www.live.com/liveMedia/public/
HOMEPAGE=		http://www.live.com/liveMedia/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

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
