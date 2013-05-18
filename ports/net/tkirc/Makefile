# $MirOS: ports/net/tkirc/Makefile,v 1.5 2007/04/13 19:27:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2004/02/02 17:35:01 sturm Exp $

COMMENT=	ircII internet relay chat client
VSN=		2.46
DISTNAME=	tkirc${VSN}
PKGNAME=	tkirc-${VSN}-${DASH_VER}
CATEGORIES=	net
HOMEPAGE=	http://netsplit.de/tkirc2/

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	ftp://ftp.netsplit.de/pub/tcltk/

RUN_DEPENDS=	:ircII-*:net/ircII \
		:tk-8.4.*:x11/tk/8.4

USE_X11=	Yes
NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

WRKDIST=	${WRKDIR}/tkirc2

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/tkirc
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/tkirc/scripts
	${INSTALL_SCRIPT} ${WRKSRC}/tkirc2 ${PREFIX}/bin/tkirc
	${INSTALL_DATA} ${WRKSRC}/{COPYING,README} ${PREFIX}/share/doc/tkirc
	${INSTALL_SCRIPT} ${WRKSRC}/.tkirc2/scripts/* \
		${PREFIX}/share/examples/tkirc/scripts
	${INSTALL_DATA} ${WRKSRC}/.tkirc2/{netscape.sh,tkircrc-example} \
		${PREFIX}/share/examples/tkirc

.include <bsd.port.mk>
