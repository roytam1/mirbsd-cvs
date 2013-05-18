# $MirOS: ports/sysutils/pciutils/Makefile,v 1.2 2006/07/21 23:40:30 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2006/03/25 21:53:35 matthieu Exp $

NOT_FOR_PLATFORMS=	*:*:sparc *:*:m68k *:*:m88k *:*:vax

COMMENT=			PCI bus configuration register access tools
DISTNAME=		pciutils-2.2.1
CATEGORIES=		sysutils
HOMEPAGE=		http://atrey.karlin.mff.cuni.cz/~mj/pciutils.shtml

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://atrey.karlin.mff.cuni.cz/pub/linux/pci/

USE_GMAKE=		Yes

EXTRA_FAKE_FLAGS+=	PREFIX=${WRKINST}${PREFIX}

NO_REGRESS=		Yes

.include <bsd.port.mk>
