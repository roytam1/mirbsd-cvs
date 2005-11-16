# $MirOS$

COMMENT=		"MirPorts Framework package tools"
CATEGORIES=		essentials infrastructure
DIST_NAME=		pkgtools
DIST_DATE=		20051116
DIST_SOURCE=		module
DIST_SOURCEDIR=		${PORTSDIR}/infrastructure/pkgtools
RESPONSIBLE=		Benny Siegert <bsiegert@mirbsd.org>
HOMEPAGE=		http://mirbsd.mirsolutions.de/?ports

# 2-clause UCB-style
# 3-clause UCB BSD
# MirOS without adv clause
# MirOS with adv clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

NO_REGRESS=		Yes

MAKE_ENV+=		PKG_USER=${BINOWN:Q}
MAKE_ENV+=		PORTSDIR=${PORTSDIR:Q}

do-configure:
	@cd ${WRKBUILD} && exec ${MAKE_PROGRAM} ${MAKE_FLAGS} obj

.include <bsd.port.mk>
