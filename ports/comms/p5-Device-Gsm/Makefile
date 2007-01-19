# $MirOS: ports/devel/p5-Carp-Clan/Makefile,v 1.1 2006/03/19 11:45:22 bsiegert Exp $

COMMENT=		interface to GSM phones or GSM modems

DISTNAME=		Device-Gsm-1.46
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		comms perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Device/}


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::comms/p5-Device-Modem

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
