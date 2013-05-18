# $MirOS: ports/essentials/pkgtools/Makefile,v 1.14 2006/02/21 03:16:58 tg Exp $

COMMENT=		"MirPorts Framework package tools"
CATEGORIES=		essentials infrastructure
CVS_DISTREPO=		_anoncvs@anoncvs.66h.42h.de:/cvs
CVS_DISTDATE=		2006/03/19 19:40
CVS_DISTMODS=		ports/infrastructure/pkgtools
CVS_DISTFILE=		pkgtools
PKGNAME=		${_CVS_DISTF:R}-0
# well it's Benny Siegert <bsiegert@> for the package tools themselves
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://www.66h.42h.de/?ports

# 2-clause UCB-style
# 3-clause UCB BSD
# MirOS without adv clause
# MirOS with adv clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

NO_REGRESS=		Yes
# used by installer, do not modify
_VERSION=		${_CVS_DISTF:R:S/${CVS_DISTFILE}-//}

MAKE_ENV+=		BINOWN=${BINOWN:Q}
MAKE_ENV+=		PORTSDIR=${PORTSDIR:Q}

do-configure:
	@cd ${WRKBUILD} && exec ${MAKE_PROGRAM} ${MAKE_FLAGS} obj

.include <bsd.port.mk>
