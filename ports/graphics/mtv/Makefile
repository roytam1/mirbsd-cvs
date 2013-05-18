# $OpenBSD: Makefile,v 1.7 2002/10/27 00:03:16 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			mpeg video player

DISTNAME=	mtv-1.0.6.0
CATEGORIES=	graphics

MASTER_SITES=	ftp://ftp.mpegtv.com/pub/mpeg/mpegtv/player/unsupported/x86-bsdi-bsdos/

HOMEPAGE=	http://www.mpegtv.com/

PERMIT_PACKAGE_CDROM=   Commercial
PERMIT_PACKAGE_FTP=     Commercial
PERMIT_DISTFILES_CDROM= Commercial
PERMIT_DISTFILES_FTP=   Commercial

EXTRACT_SUFX=	.tgz

WRKDIST=        ${WRKDIR}/mtv

NO_BUILD=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/mtv
	${INSTALL_SCRIPT} ${WRKSRC}/mtv ${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKSRC}/mtvp ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/COPYRIGHT ${PREFIX}/share/mtv
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/mtv
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/mtv
	${INSTALL_DATA} ${WRKSRC}/release-notes.html ${PREFIX}/share/mtv

.include <bsd.port.mk>
