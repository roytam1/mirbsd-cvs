# $MirOS: ports/sysutils/pciutils/Makefile,v 1.3 2006/09/14 00:13:41 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2006/03/25 21:53:35 matthieu Exp $

NOT_FOR_PLATFORMS=	*:*:sparc *:*:m68k *:*:m88k *:*:vax

COMMENT=		PCI bus configuration register access tools
DISTNAME=		pciutils-2.2.10
CATEGORIES=		sysutils
HOMEPAGE=		http://atrey.karlin.mff.cuni.cz/~mj/pciutils.shtml

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://atrey.karlin.mff.cuni.cz/pub/linux/pci/

USE_GMAKE=		Yes
EXTRA_XAKE_FLAGS+=	PREFIX=${PREFIX:Q}
NO_REGRESS=		Yes

.include <bsd.port.mk>
