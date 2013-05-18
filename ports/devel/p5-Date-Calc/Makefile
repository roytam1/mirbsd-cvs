# $MirOS: ports/devel/p5-Date-Calc/Makefile,v 1.5 2006/03/19 14:22:05 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/01/17 15:58:08 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			date calculations for the Gregorian calendar

DISTNAME=	Date-Calc-5.4
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	devel perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Date/}


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

RUN_DEPENDS+=	:p5-Carp-Clan-*:devel/p5-Carp-Clan
RUN_DEPENDS+=	:p5-Bit-Vector->=6.2:math/p5-Bit-Vector
BUILD_DEPENDS+=	${RUN_DEPENDS}

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
