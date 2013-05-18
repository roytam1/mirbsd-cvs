# $MirOS: ports/astro/xworld/Makefile,v 1.1.7.1 2005/03/18 15:42:49 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/03/31 12:35:52 sturm Exp $

BROKEN=		configure script requires csh

COMMENT=	"earth as seen from the direction of the sun"

DISTNAME=	xworld-2.0
CATEGORIES=	astro x11


MASTER_SITES=	ftp://gutemine.geo.uni-koeln.de/pub/xworld/ \
		ftp://ftp.Uni-Koeln.DE/misc/

# BSD
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_X11=	Yes

INSTALL_STRIP=
NO_REGRESS=	Yes

pre-build:
	cd ${WRKSRC} && \
	CC="${CC}" CFLAGS="${CFLAGS}" INSTALL=install \
	CAT=cat STRIP=strip INCLUDES="-I${X11BASE}/include" \
	LDLIBS="-lm -L${X11BASE}/lib -lX11" MORELIBS="" \
	/bin/csh ./configure	

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/xworld ${PREFIX}/bin

.include <bsd.port.mk>
