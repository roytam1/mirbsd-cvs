# $MirOS: ports/astro/xworld/Makefile,v 1.5 2008/10/04 19:02:55 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/03/31 12:35:52 sturm Exp $

COMMENT=		earth as seen from the direction of the sun
DISTNAME=		xworld-2.0
CATEGORIES=		astro x11
MASTER_SITES=		ftp://gutemine.geo.uni-koeln.de/pub/xworld/ \
			ftp://ftp.Uni-Koeln.DE/misc/

# BSD
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_X11=		Yes
BUILD_DEPENDS+=		::shells/csh
INSTALL_STRIP=		# empty, it crashes then
NO_REGRESS=		Yes

pre-build:
	cd ${WRKSRC} && \
	    CC=${_PASS_CC:T:Q} CFLAGS=${CFLAGS:M*:Q} INSTALL=${INSTALL:Q} \
	    INCLUDES= CAT=cat STRIP=strip MORELIBS=${LDFLAGS:Q} \
	    LDLIBS='-lm -lX11' ${LOCALBASE}/bin/csh configure

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/xworld ${PREFIX}/bin/

.include <bsd.port.mk>
