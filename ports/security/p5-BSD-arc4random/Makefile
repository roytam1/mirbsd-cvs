# $MirOS: ports/security/p5-BSD-arc4random/Makefile,v 1.6 2009/11/29 15:58:46 tg Exp $

COMMENT=		Perl bindings for the arc4random API
CATEGORIES=		security devel perl5
DISTNAME=		BSD-arc4random-1.50
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=BSD/} \
			${_MASTER_SITE_MIRBSD:distfiles/=dist/hosted/p5/}

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
