# $MirOS: ports/essentials/pkgtools/Makefile,v 1.41 2007/07/10 22:26:46 tg Exp $
#-
# This port should contain no patches, to aid the installer,
# and have no dependencies, to aid the upgrading sysop.

COMMENT=		MirPorts Framework package tools
CATEGORIES=		essentials infrastructure
DISTNAME=		pkgtools-${_VERSION}
# do not change the name of the following variable, Setup.sh(8) depends on it!
_VERSION=		20070726
# well it's Benny Siegert <bsiegert@> for the package tools themselves
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://mirbsd.de/ports
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/pkgtools/}
EXTRACT_SUFX=		.cgz

# 2-clause UCB-style
# 3-clause UCB BSD
# MirOS without adv clause
# MirOS with adv clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# never ever set a flavour from the list below manually!
FLAVORS=		opt_t

WRKDIST=		${WRKDIR}/pkgtools
NO_REGRESS=		Yes
MAKE_ENV+=		BINOWN=${BINOWN:Q}
MAKE_ENV+=		PORTSDIR=${PORTSDIR:Q}

do-configure:
	@cd ${WRKBUILD} && exec ${MAKE_PROGRAM} ${MAKE_FLAGS} obj

.include <bsd.port.mk>

_CIPHERS+=		cksum
