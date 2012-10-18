# $MirOS: ports/emulators/qemu/guest-agent/Makefile,v 1.1 2012/10/17 23:24:37 tg Exp $

COMMENT=		QEMU Guest Agent
CATEGORIES=		emulators
VSN=			1.2.0
PKGNAME=		qemu-ga-${VSN}-${DASH_VER}
DISTNAME=		qemu-${VSN}
HOMEPAGE=		http://wiki.qemu.org/Features/QAPI/GuestAgent
MASTER_SITES=		http://wiki.qemu.org/download/
EXTRACT_SUFX=		.tar.bz2

# GPLv2/LGPLv2/BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

BUILD_DEPENDS+=		:python->=2.4,<=3.0:lang/python/2.5
LIB_DEPENDS+=		glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib
USE_GMAKE=		Yes
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q} \
			--cc=${_PASS_CC:T:Q} \
			--make=${GMAKE:Q} \
			--enable-guest-agent
ALL_TARGET=		qemu-ga
NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/qemu-ga ${PREFIX}/libexec/

.include <bsd.port.mk>
