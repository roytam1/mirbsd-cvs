# $OpenBSD: Makefile,v 1.10 2004/02/01 20:22:18 sturm Exp $
#
# Many variables moved to ../Makefile.inc

COMMENT=			English dictionary for the Amaya browser/page composer

PKGNAME=		amaya-english-dict-20011029-0
DISTNAME=		English

RUN_DEPENDS=		${DICT_RUN_DEPENDS}

NO_BUILD=		Yes
NO_REGRESS=		Yes
PKG_ARCH=		*

DICNAME=		Eprinc

do-install:
	${dict_install_frag}

.include <bsd.port.mk>
