# $MirOS$
# $OpenBSD: Makefile,v 1.2 2004/02/27 01:08:34 brad Exp $

COMMENT=	framework for parsing the Perl Pod format

DISTNAME=	Pod-Simple-3.05
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Pod/}

B_R_DEPENDS=	::textproc/p5-Pod-Escapes

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
