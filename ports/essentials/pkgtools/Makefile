# $MirOS: ports/essentials/pkgtools/Makefile,v 1.6 2006/01/11 13:14:02 tg Exp $

COMMENT=		"MirPorts Framework package tools"
CATEGORIES=		essentials infrastructure
CVS_DISTREPO=		_anoncvs@thor.66h.42h.de:/cvs
CVS_DISTDATE=		2005/12/30
CVS_DISTMODS=		ports/infrastructure/pkgtools
CVS_DISTFILE=		pkgtools
PKGNAME=		${_CVS_DISTF:R}-0
RESPONSIBLE=		Benny Siegert <bsiegert@mirbsd.org>
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

MAKE_ENV+=		PKG_USER=${BINOWN:Q}
MAKE_ENV+=		PORTSDIR=${PORTSDIR:Q}

do-configure:
	@cd ${WRKBUILD} && exec ${MAKE_PROGRAM} ${MAKE_FLAGS} obj

.include <bsd.port.mk>
