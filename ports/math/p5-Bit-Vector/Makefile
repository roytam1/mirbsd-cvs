# $MirOS: ports/math/p5-Bit-Vector/Makefile,v 1.6 2006/09/14 00:11:00 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/01/17 15:58:08 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			library of advanced math functions

DISTNAME=	Bit-Vector-6.4
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	math perl5


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=   ${MASTER_SITE_PERL_CPAN:=Bit/}

B_R_DEPENDS+=	:p5-Carp-Clan-*:devel/p5-Carp-Clan

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
