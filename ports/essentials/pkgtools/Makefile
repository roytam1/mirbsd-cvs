# $MirOS: ports/essentials/pkgtools/Makefile,v 1.54 2009/10/24 18:42:17 tg Exp $
#-
# This port should contain no patches, to aid the installer,
# and have no dependencies, to aid the upgrading sysop.

COMMENT=		MirPorts Framework package tools
CATEGORIES=		essentials infrastructure
DISTNAME=		pkgtools-${_VERSION}
CVS_DISTDATE=		2009/11/22 20:00
# actually it’s Benny Siegert <bsiegert@> for the package tools themselves
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://mirbsd.de/ports
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/pkgtools/}
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTMODS=		pkgtools
MCZ_FETCH=		Yes

# 2-clause UCB-style
# 3-clause UCB BSD
# MirOS without adv clause
# MirOS with adv clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# never ever set a flavour from the list below manually!
FLAVOURS=		opt_t

NO_REGRESS=		Yes
MAKE_ENV+=		BINOWN=${BINOWN:Q}
MAKE_ENV+=		PORTSDIR=${PORTSDIR:Q}

do-configure:
	@cd ${WRKBUILD} && exec ${MAKE_PROGRAM} ${MAKE_FLAGS} obj

.include <bsd.port.mk>

_CIPHERS+=		cksum
